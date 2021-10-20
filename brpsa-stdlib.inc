/* ---------------------------------------------------------------------------- */
/*      Blefonix RolePlay Standard Library                                      */
/* ---------------------------------------------------------------------------- */

// built-in include guard removal, just in case if the
// user has a local dependency with the same file name
#if defined _inc_brpsa_stdlib
	#undef _inc_brpsa_stdlib
#endif

// custom include-guard to
// ensure we don't duplicate
#if defined _brpsa_stdlib_included
	#endinput
#endif
#define _brpsa_stdlib_included

/* ---------------------------------------------------------------------------- */
/*      https://github.com/brpsamp/brpsa-stdlib                                 */
/* ---------------------------------------------------------------------------- */

#include <a_samp>
#include <logger>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_va>
#include <stdlib-vars>

hook OnScriptInit() {
    #if !defined BRPSA_NO_LOG
        Logger_ToggleDebug("brpsa-stdlib", true);
    #endif
    #if !defined BRPSA_NO_INFO
       print("\nOnScriptInit |> brpsa-stdlib:0.0.1\n");
    #endif
    return true;
}
