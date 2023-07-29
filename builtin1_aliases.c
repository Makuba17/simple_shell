#include "shell.h"

/**
 * showCommandHistory - Displays the history list, one command per line, preceded
 *                      with line numbers, starting at 0.
 * @shellData: Structure containing potential arguments. Used to maintain
 *             a constant function prototype.
 * Return: Always 0
 */
int showCommandHistory(shellData_t *shellData)
{
    print_list(shellData->history);
    return 0;
}

/**
 * unsetShellAlias - Unsets an alias to a string.
 * @shellData: Parameter struct.
 * @aliasStr: The string alias.
 * Return: Always 0 on success, 1 on error
 */
int unsetShellAlias(shellData_t *shellData, char *aliasStr)
{
    char *equalSign, c;
    int ret;

    equalSign = _strchr(aliasStr, '=');
    if (!equalSign)
        return 1;
    c = *equalSign;
    *equalSign = 0;
    ret = delete_node_at_index(&(shellData->alias),
                               get_node_index(shellData->alias, node_starts_with(shellData->alias, aliasStr, -1)));
    *equalSign = c;
    return ret;
}

/**
 * setShellAlias - Sets an alias to a string.
 * @shellData: Parameter struct.
 * @aliasStr: The string alias.
 * Return: Always 0 on success, 1 on error
 */
int setShellAlias(shellData_t *shellData, char *aliasStr)
{
    char *equalSign;

    equalSign = _strchr(aliasStr, '=');
    if (!equalSign)
        return 1;
    if (!*++equalSign)
        return unsetShellAlias(shellData, aliasStr);

    unsetShellAlias(shellData, aliasStr);
    return add_node_end(&(shellData->alias), aliasStr, 0) == NULL;
}

/**
 * printShellAlias - Prints an alias string.
 * @aliasNode: The alias node.
 * Return: Always 0 on success, 1 on error
 */
int printShellAlias(list_t *aliasNode)
{
    char *equalSign = NULL, *aliasValue = NULL;

    if (aliasNode)
    {
        equalSign = _strchr(aliasNode->str, '=');
        for (aliasValue = aliasNode->str; aliasValue <= equalSign; aliasValue++)
            _putchar(*aliasValue);
        _putchar('\'');
        _puts(equalSign + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * aliasShellCommand - Mimics the alias builtin (man alias).
 * @shellData: Structure containing potential arguments. Used to maintain
 *             a constant function prototype.
 * Return: Always 0
 */
int aliasShellCommand(shellData_t *shellData)
{
    int i = 0;
    char *equalSign = NULL;
    list_t *aliasNode = NULL;

    if (shellData->argc == 1)
    {
        aliasNode = shellData->alias;
        while (aliasNode)
        {
            printShellAlias(aliasNode);
            aliasNode = aliasNode->next;
        }
        return 0;
    }

    for (i = 1; shellData->argv[i]; i++)
    {
        equalSign = _strchr(shellData->argv[i], '=');
        if (equalSign)
            setShellAlias(shellData, shellData->argv[i]);
        else
            printShellAlias(node_starts_with(shellData->alias, shellData->argv[i], '='));
    }

    return 0;
}

