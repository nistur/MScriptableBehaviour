#ifndef _M_SCRIPTABLE_BEHAVIOUR_H
#define _M_SCRIPTABLE_BEHAVIOUR_H

#include <MEngine.h>


class MScriptableBehaviour : public MBehavior
{
public:

    // constructors / destructors
    MScriptableBehaviour(MObject3d * parentObject);
    MScriptableBehaviour(MScriptableBehaviour & behavior, MObject3d * parentObject);
    ~MScriptableBehaviour(void);

    // destroy
    void destroy(void);

    // get new
    static MBehavior * getNew(MObject3d * parentObject);

    // get copy
    MBehavior * getCopy(MObject3d * parentObject);

    // name
    const char * getName(void);
    void setUserData(void* userData);

    // variables
    unsigned int getVariablesNumber(void);
    MVariable getVariable(unsigned int id);

    // events (virtuals from MBehavior class)
    void update(void);
    void runEvent(int param){}

private:
    const char* m_Name;

    bool m_Init;
};

#endif