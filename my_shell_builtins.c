#include "shell.h"

/**
 * Function: exitShell
 * Description: Exits the shell program.
 * Arguments:
 *   - shellData: Structure containing potential arguments. Used to maintain
 *                a constant function prototype.
 * Return: Exits with a given exit status
 *         (0) if shellData->args[0] != "exit"
 */
int exitShell(shellData_t *shellData)
{
    int exitCheck;

    if (shellData->args[1])  // Check if there is an exit argument.
    {
        exitCheck = err_atoi(shellData->args[1]);
        if (exitCheck == -1)
        {
            shellData->status = 2;
            printErrorMessage(shellData, "Illegal number: ");
            _eputs(shellData->args[1]);
            _eputchar('\n');
            return 1;
        }
        shellData->errorNumber = err_atoi(shellData->args[1]);
        return -2;
    }
    shellData->errorNumber = -1;
    return -2;
}

/**
 * Function: changeDirectory
 * Description: Changes the current directory of the shell process.
 * Arguments:
 *   - shellData: Structure containing potential arguments. Used to maintain
 *                a constant function prototype.
 * Return: Always 0
 */
int changeDirectory(shellData_t *shellData)
{
    char *currentDir, *targetDir, buffer[1024];
    int chdirResult;

    currentDir = getcwd(buffer, 1024);
    if (!currentDir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!shellData->args[1])
    {
        targetDir = shellGetEnvironment(shellData, "HOME=");
        if (!targetDir)
            chdirResult = /* TODO: Decide what this should be? */
                chdir((targetDir = shellGetEnvironment(shellData, "PWD=")) ? targetDir : "/");
        else
            chdirResult = chdir(targetDir);
    }
    else if (_strcmp(shellData->args[1], "-") == 0)
    {
        if (!shellGetEnvironment(shellData, "OLDPWD="))
        {
            _puts(currentDir);
            _putchar('\n');
            return 1;
        }
        _puts(shellGetEnvironment(shellData, "OLDPWD=")), _putchar('\n');
        chdirResult = /* TODO: Decide what this should be? */
            chdir((targetDir = shellGetEnvironment(shellData, "OLDPWD=")) ? targetDir : "/");
    }
    else
        chdirResult = chdir(shellData->args[1]);

    if (chdirResult == -1)
    {
        printErrorMessage(shellData, "can't cd to ");
        _eputs(shellData->args[1]), _eputchar('\n');
    }
    else
    {
        shellSetEnvironment(shellData, "OLDPWD", shellGetEnvironment(shellData, "PWD="));
        shellSetEnvironment(shellData, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * Function: showHelp
 * Description: Displays help information for the shell.
 * Arguments:
 *   - shellData: Structure containing potential arguments. Used to maintain
 *                a constant function prototype.
 * Return: Always 0
 */
int showHelp(shellData_t *shellData)
{
    char **argumentsArray;

    argumentsArray = shellData->args;
    _puts("Help function call works. Function not yet implemented.\n");
    if (0)
        _puts(*argumentsArray); /* Temp unused workaround */

    return 0;
}
