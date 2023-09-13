#define PATHS_BUFFER 256
#define COMMAND_BUFFER 2048

const char *version = "0.0.2";
const char *prompt = "$ ";
const char *helpDocs = "TODO: When man command is completed";

const char paths[PATHS_BUFFER][PATHS_BUFFER] = {
    "~/.local/bin/",
    "/usr/local/bin/",
    "/usr/bin/",
    "/bin/"
};
