#include "MScriptableBehaviourPlugin.h"
#include "MScriptableBehaviour.h"

#include <cstring>

vector<char*> s_BehaviourNames;

void MPluginStart(MScriptableBehaviour)
{
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
}