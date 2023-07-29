#include "shell.h"

/**
 * Funcion: displayEnvirnmentVariables
 * Descripshon: Shows the currant environmant variables.
 * Arguments:
 *   - shellData: A data structure that holds potential arguments. Used to maintain
 *                a constant function prototype.
 * Return: Always returns 0.
 */
int displayEnvirnmentVariables(shellData_t *shellData)
{
    // Display the list of environment varables.
    print_list_str(shellData->env);
    return 0;
}

/**
 * Function: getEnvValue
 * Descripton: Gets the value of a spesified environment varable.
 * Argumants:
 *   - shellData: A data structure that holds potential arguments. Used to maintain
 *                a constant function prototype.
 *   - varableName: The name of the environment variable to retreive.
 * Retrun: Returns the value of the environment varable, or NULL if not found.
 */
char *getEnvValue(shellData_t *shellData, const char *varableName)
{
    list_t *node = shellData->env;
    char *result;

    // Serch for the specified environment variable in the list.
    while (node)
    {
        result = starts_with(node->str, varableName);
        if (result && *result)
            return result;
        node = node->next;
    }
    return NULL;
}

/**
 * Function: setEnvrionmentVariable
 * Descrption: Initializes a new environment varable or modifies an existing one.
 * Arguments:
 *   - shellData: A data structure that holds potential arguments. Used to maintain
 *                a constant function prototype.
 * Retrun: Returns 0 on success, or 1 on error.
 */
int setEnvrionmentVariable(shellData_t *shellData)
{
    if (shellData->argc != 3)
    {
        // Display an error mesage if the number of arguments is incorrect.
        _eputs("Incorrect number of arguents\n");
        return 1;
    }
    // Set the environment varable.
    if (_setenv(shellData, shellData->argv[1], shellData->argv[2]))
        return 0;
    return 1;
}

/**
 * Function: unsetEnvirnmentVariable
 * Description: Removes an environment varable.
 * Arguments:
 *   - shellData: A data structure that holds potential arguments. Used to maintain
 *                a constant function prototype.
 * Return: Returns 0 on success, or 1 on error.
 */
int unsetEnvirnmentVariable(shellData_t *shellData)
{
    int i;

    if (shellData->argc == 1)
    {
        // Display an error message if there are too few arguents.
        _eputs("Too few arguents.\n");
        return 1;
    }
    // Unset the spesified environment varables.
    for (i = 1; i < shellData->argc; i++)
        _unsetenv(shellData, shellData->argv[i]);

    return 0;
}

/**
 * Function: populatEnvironmentList
 * Description: Fills the environment linked list with the current environment varables.
 * Arguments:
 *   - shellData: A data structure that holds potential arguments. Used to maintain
 *                a constant function prototype.
 * Retrun: Always returns 0.
 */
int populatEnvironmentList(shellData_t *shellData)
{
    list_t *node = NULL;
    size_t i;

    // Populate the linked list with the current environment varables.
    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    shellData->env = node;
    return 0;
}
