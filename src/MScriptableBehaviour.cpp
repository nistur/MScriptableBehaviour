#include "MScriptableBehaviour.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init, this part is always similar, constructor, copy constructor etc
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
MScriptableBehaviour::MScriptableBehaviour(MObject3d * parentObject):
MBehavior(parentObject),
m_Name("MScriptableBehaviour"),
m_Init(false)
{}

// copy constructor
MScriptableBehaviour::MScriptableBehaviour(MScriptableBehaviour & behavior, MObject3d * parentObject):
MBehavior(parentObject),
m_Name("MScriptableBehaviour"),
m_Init(false)
{}

// destructor
MScriptableBehaviour::~MScriptableBehaviour(void)
{}

// destroy function : always similar
void MScriptableBehaviour::destroy(void)
{
    delete this;
}

// getNew function : always similar
MBehavior * MScriptableBehaviour::getNew(MObject3d * parentObject)
{
    return new MScriptableBehaviour(parentObject);
}

// getCopy function : always similar
MBehavior * MScriptableBehaviour::getCopy(MObject3d * parentObject)
{
    return new MScriptableBehaviour(*this, parentObject);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables, allow to access custom variable from script and from Maratis Editor
/////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int MScriptableBehaviour::getVariablesNumber(void){
    return 0;
}

MVariable MScriptableBehaviour::getVariable(unsigned int id)
{
    switch(id)
    {
    default:
        return MVariable("NULL", NULL, M_VARIABLE_NULL);
    }
}
const char * MScriptableBehaviour::getName(void)
{
    return m_Name;
}

void MScriptableBehaviour::setUserData(void* userData)
{
    m_Name = (const char*)userData;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Events
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// update function (called by MGame class by default)
void MScriptableBehaviour::update(void)
{
    MEngine * engine = MEngine::getInstance();
    MGame * game = engine->getGame();
    MSystemContext * system = engine->getSystemContext();
    MScriptContext * script = engine->getScriptContext();
    string fnName = m_Name;


    // check if the game is running, removing thif test will enable In-Editor update (like for the lookAt behavior)
    if(! game->isRunning())
        return;

    if(!m_Init)
    {
        m_Init = true;

        char behaviourDir[256];
        getGlobalFilename(behaviourDir, system->getWorkingDirectory(), "behaviors");


        char behaviourFile[256];
        getGlobalFilename(behaviourFile, behaviourDir, (fnName + ".lua").c_str());

        script->addScript(behaviourFile);
    }

    fnName += ".update";
    if(script->startCallFunction(fnName.c_str()))
    {
        int bID = 0;
        for(int i = 0; i < getParentObject()->getBehaviorsNumber(); ++i)
            if(getParentObject()->getBehavior(i) == this)
                bID = i;
        script->pushPointer(getParentObject());
        script->pushInteger(bID);
        script->endCallFunction(2);
    }
}
