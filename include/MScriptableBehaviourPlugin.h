#ifndef __M_SCRIPTABLE_BEHAVIOUR_PLUGIN_H__
#define __M_SCRIPTABLE_BEHAVIOUR_PLUGIN_H__

#ifdef WIN32
# include <windows.h>
# ifdef M_SCRIPTABLE_BEHAVIOUR_BUILD
#  define EXPORT __declspec(dllexport)
# else
#  define EXPORT __declspec(dllimport)
# endif
#else
# define EXPORT
#endif

#ifdef  MPluginStart
# undef MPluginStart
#endif/*MPluginStart*/

#ifdef  MPluginEnd
# undef MPluginEnd
#endif/*MPluginEnd*/

#ifdef  M_SCRIPTABLE_BEHAVIOUR_STATIC

#define MPluginStart(x) \
x##Start()

#define MPluginEnd(x)  \
x##End()

#else/*!M_SCRIPTABLE_BEHAVIOUR_STATIC*/

#define MPluginStart(x) \
StartPlugin()

#define MPluginEnd(x)  \
EndPlugin()

#endif/*M_SCRIPTABLE_BEHAVIOUR_STATIC*/

extern "C"
{

EXPORT void MPluginStart(MScriptableBehaviour);
EXPORT void MPluginEnd  (MScriptableBehaviour);

}
#endif/*__M_SCRIPTABLE_BEHAVIOUR_PLUGIN_H__*/