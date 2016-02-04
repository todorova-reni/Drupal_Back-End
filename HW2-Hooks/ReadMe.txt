We have 2 modules
Module A:
Has a config page ("admin/config/content/modulea-config"), which is only 
accessible by people with permission "administer modulea". It has hook, 
called hook_modulea_config (no params, returns string). It is called in
the config form of our module and it gets all the information, returned by 
other modules (which implements the same hook) and return the name of
the module and the value which the implemented hook returns.
Module B:
It depends on module A. It has 2 hooks. First hook implements 
"hook_modulea_config" and return string ("This text comes from module B")
The second hook is for alter of the configure form and adds new text field.