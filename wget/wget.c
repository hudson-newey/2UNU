#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "wget.h"

#define OUTPUT_FILE "index.html"

struct MemoryStruct
{
    char *memory;
    size_t size;
};

bool fileExist(const char *filePath)
{
    struct stat buffer;
    return stat(filePath, &buffer) == 0;
}

void deleteFile(const char *filePath)
{
    if (fileExist(filePath))
    {
        remove(filePath);
    }
}

void writeToFile(const char *filePath, char *contents)
{
    FILE *fp = fopen(filePath, "w");
    fprintf(fp, "%s", contents);
    fclose(fp);
}

// Callback function to write data received from the webpage
size_t memoryWriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + real_size + 1);
    if (mem->memory == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, real_size);
    mem->size += real_size;
    mem->memory[mem->size] = '\0';

    return real_size;
}

// Function to retrieve webpage contents as char*
char *fetchWebpageContent(const char *url)
{
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1); // Start with a small initial size
    if (chunk.memory == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memoryWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(chunk.memory);
            return NULL;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return chunk.memory;
}

// TODO: this isn't currently functional, I should probably make it work properly
void debugInfo(const char *url)
{
    printf(
        "--Redacted Time--  %s/\nResolving %s (%s)... Redacted IPV6, Redacted IPV4\nConnecting to %s (%s)|Redacted IPV6|:80... connected.\nHTTP request sent, awaiting response... 200 OK\nLength: unspecified [text/html]\nSaving to: '%s'\n\n%s\t\t[ <=>                                             ]  19.03K  --.-KB/s    in 0.04s\n\nRedacted Date Redacted Time (524 KB/s) - '%s' saved [19483]\n",
        url,
        url,
        url,
        url,
        url,
        OUTPUT_FILE,
        OUTPUT_FILE,
        OUTPUT_FILE
    );
}

int downloadWebpage(const char *url)
{
    deleteFile(OUTPUT_FILE);

    debugInfo(url);

    char *content = fetchWebpageContent(url);
    writeToFile(OUTPUT_FILE, content);

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("wget: missing URL\nUsage: wget [OPTION]... [URL]...\n\nTry `wget --help' for more options.\n");
        return 1;
    }

    if (strcmp(argv[1], "--version") == 0)
    {
        printf("%s\n", version);
        return 0;
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        printf("%s\n", helpDocs);
        return 0;
    }

    const char *websiteUrl = argv[1];
    return downloadWebpage(websiteUrl);
}
