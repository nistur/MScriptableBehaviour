#include "MScriptableBehaviourPlugin.h"
#include "MScriptableBehaviour.h"

#include <cstring>

#include "MScriptableBehaviorPublishEventsLua.c"

#ifdef  M_USE_EMBED_FILE
# include "MEmbedFile.h"
#else
# define EMBEDDED(dir, file)
# define EMBED(dir, file)
# define UNEMBED(dir, file)
#endif/*M_USE_EMBED_FILE*/

#ifdef  M_USE_GAME_EVENT
#ifdef  M_USE_SCRIPT_EXT
#include "MScriptExt.h"
#include "MScriptableBehaviourLua.c"
#include "MEventListener.h"

class MScriptableBehaviourEventListener : public MEventListener
{
public:
    MEventListenerDeclare(MScriptableBehaviourEventListener);
    void onEvent(const char* event)
    {
        if(strcmp(event, "MScriptInit") == 0)
        {
            MScriptExt* script = NULL;
            MScriptExtGet(script);
            if(script)
            {
                script->parse(scriptsMScriptableBehaviour, 
                              scriptsMScriptableBehaviourName, 
                              scriptsMScriptableBehaviourSize);
#ifndef M_USE_EMBED_FILE
                script->parse(editorMScriptableBehaviorPublishEvents,
                              editorMScriptableBehaviorPublishEventsName,
                              editorMScriptableBehaviorPublishEventsSize);
#endif/*M_USE_EMBED_FILE*/
            }
        }
    }
};

MScriptableBehaviourEventListener s_scriptableBehaviourScriptEventListener;
#endif/*M_USE_SCRIPT_EXT*/
#endif/*M_USE_GAME_EVENT*/

vector<char*> s_BehaviourNames;

EMBEDDED(editor, MScriptableBehaviorPublishEvents);

void MPluginStart(MScriptableBehaviour)
{
    EMBED(editor, MScriptableBehaviorPublishEvents);
    // get engine
    MEngine * engine = MEngine::getInstance();
    MSystemContext* system = engine->getSystemContext();
    MScriptContext* script = engine->getScriptContext();
    MBehaviorManager * behaviorManager = engine->getBehaviorManager();

    // add behaviors
    char behaviourDir[256];
    getGlobalFilename(behaviourDir, system->getWorkingDirectory(), "behaviors");

    vector<string> files;
    readDirectory(behaviourDir, &files);

    for(vector<string>::iterator iFile = files.begin();
        iFile != files.end();
        iFile++)
    {
        if(iFile->find(".lua") != string::npos)
        {
            std::string _behaviourName = iFile->substr(0, iFile->find_last_of('.'));
            char* behaviourName = new char[_behaviourName.length() + 1];
            memcpy(behaviourName, _behaviourName.c_str(), _behaviourName.length() + 1);
            s_BehaviourNames.push_back(behaviourName);

            behaviorManager->addBehavior( behaviourName, 
                                          M_OBJECT3D, 
                                          MScriptableBehaviour::getNew, 
                                          behaviourName );
        }
    }
    //behaviorManager->addBehavior(MyBehavior::getStaticName(), M_OBJECT3D, MyBehavior::getNew);
}

void MPluginEnd(MScriptableBehaviour)
{
    for(vector<char*>::iterator iBehaviour = s_BehaviourNames.begin();
        iBehaviour != s_BehaviourNames.end();
        iBehaviour++)
    {
        delete [] *iBehaviour;
    }

    s_BehaviourNames.clear();
    UNEMBED(editor, MScriptableBehaviorPublishEvents);
}