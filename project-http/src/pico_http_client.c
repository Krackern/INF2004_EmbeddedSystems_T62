//
// Created by Kevin Rodrigues on 16/10/2023.
//

#include "pico_http_client/pico_http_client.h"

static const char *method2string(enum HTTPMethod method) {
    const char *methods[] = {"OPTIONS", "GET", "HEAD", "POST", "PUT",
                             "DELETE", "TRACE", "CONNECT", NULL};
    return methods[method];
}

static url_t parse_url(const char *url) {
    url_t result;

    char scheme[10], domain[64], port[64], path[1024], query[1024];
    if (sscanf(url, "%9[^:]://%63[^:?]:%63[^/?]%1023[^?]%1023s", scheme, domain, port, path, query) < 4) {
        sscanf(url, "%9[^:]://%63[^:/?]%1023[^?]%1023s", scheme, domain, path, query);
        port[0] = '8';
        port[1] = '0';
        port[2] = 0;
    }
    result.scheme = strdup(scheme);
    result.domain = strdup(domain);
    result.port = strdup(port);
    result.path = strdup(path);
    result.query = strdup(query);
    return result;
}

static void free_url(url_t *url) {
    free(url->domain);
    free(url->port);
    free(url->path);
    free(url->scheme);
    free(url->query);
}

static http_response_t parse_response(char *body, int body_length) {
    http_response_t response;
    char http_version[10];
    sscanf(body, "%[^ ] %d", http_version, &response.code);
    char *res = strstr(body, "\r\n\r\n");
    if (res != NULL) {
        int content_length = body_length - 4 - (res - body);
        response.body = calloc(1, content_length + 1);
        memcpy(response.body, res + 4, content_length);
        response.body[content_length] = 0;
    }
    return response;
}

int add_header(http_client_t *http_client, const char *key, const char *value) {
    int size = strlen(key) + strlen(value) + 5;
    if (http_client->headers == NULL) {
        http_client->headers = (char *) calloc(1, size);
    } else {
        void *tmp = realloc(http_client->headers, http_client->header_len + size);
        if (tmp == NULL) {
            free(http_client->headers);
            return 0;
        }
        http_client->headers = (char *) tmp;
        memset(http_client->headers + http_client->header_len, 0, size);
    }
    int writed = snprintf(http_client->headers,
                          http_client->header_len + size,
                          "%s%s: %s\r\n",
                          http_client->headers,
                          key,
                          value);
    http_client->header_len += writed;
    return writed;
}

http_client_t *new_http_client(const char *url) {
    http_client_t *client = (http_client_t *) calloc(1, sizeof(http_client_t));
    client->url = strdup(url);
    return client;
}

void free_http_client(http_client_t *http_client) {
    free(http_client->headers);
    free(http_client->data);
    free(http_client->url);
    free(http_client);
}

http_response_t http_request(const char *method, http_client_t *http_client, const char *post_data) {
//http_response_t http_request(enum HTTPMethod method, http_client_t *http_client, const char *post_data) {
    http_response_t response;
    int data_size;
    response.code = -1;
    response.body = NULL;

    add_header(http_client, "User-Agent", "PicoW");

    unsigned int bufsize = BUFSIZ + http_client->header_len;    
    printf("Post-data 2: %s\n", post_data);
    if(post_data != NULL){
        //POST
        bufsize += (strlen(post_data) + 5);
    }

    url_t url = parse_url(http_client->url);
    char *data = (char *) calloc(1, bufsize);
    if (data == NULL) {
        return response;
    }
    printf("Data: %s\n", http_client->headers);

    // int data_size = snprintf(data,
    //                          bufsize,
    //                          "%s %s HTTP/1.1\r\n"
    //                          "Host: %s:%s\r\n"
    //                          "Accept: */*\r\n"
    //                          "%s"
    //                          "Connection: close\r\n\r\n",
    //                          method2string(method),
    //                          url.path,
    //                          url.domain,
    //                          url.port,
    //                          http_client->headers == NULL ? "" : http_client->headers);
    
//Test
    if (method == "GET") {
        data_size = snprintf(data,
                                bufsize,
                                "GET %s HTTP/1.1\r\n"
                                "Host: %s:%s\r\n"
                                "Accept: */*\r\n"
                                "%s"
                                "Connection: close\r\n\r\n",
                                //method2string(method),
                                url.path,
                                url.domain,
                                url.port,
                                http_client->headers == NULL ? "" : http_client->headers);
                                         
    } else if (method == "POST") {
        data_size = snprintf(data,
                                bufsize,
                                "POST %s HTTP/1.1\r\n"
                                "Host: %s:%s\r\n"
                                "Accept: */*\r\n"
                                "%s"
                                "Content-Length: %zu\r\n"
                                "Connection: close\r\n\r\n%s",
                                //method2string(method),
                                url.path,
                                url.domain,
                                url.port,
                                http_client->headers == NULL ? "" : http_client->headers,
                                strlen(post_data),
                                post_data);
    }
//Test
    printf("bufsize: %i\n", bufsize);
    printf("Data: %s\n", data);
    printf("Data size: %i\n", data_size);
    perror("snprintf");
    if (handle_socket(http_client, &url, data, data_size) > 0) {
        response = parse_response(http_client->data, http_client->data_size);
//        printf("%s\n", response.body);
    }

    free(data);
    free_url(&url);
    return response;
}
