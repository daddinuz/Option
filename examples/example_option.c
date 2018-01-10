/*
 * C Source File
 *
 * Author: daddinuz
 * email:  daddinuz@gmail.com
 * Date:   January 10, 2018
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <option.h>

/*
 *
 */
#define truth(x) \
    ((x) ? "true" : "false")

static OptionOf(char *) String_new(const char *literal);
static OptionOf(char *) String_mapFn(OptionOf(char *) optionalString);
static OptionOf(char *) String_defFn(void);

/*
 *
 */
int main() {
    OptionOf(char *) option = String_new("Just a string");

    puts("Option:");
    printf("\tisSome:    %s\n", truth(Option_isSome(option)));
    printf("\tisNone:    %s\n", truth(Option_isNone(option)));
    printf("\texpect:    %s\n", (char *) Option_expect(option, "%s", "Expected a string."));
    printf("\tmap:       %s\n", (char *) Option_unwrap(Option_map(option, String_mapFn)));
    printf("\tmapOr:     %s\n", (char *) Option_unwrap(Option_mapOr(None, String_new("Default string"), String_mapFn)));
    printf("\tmapOrElse: %s\n", (char *) Option_unwrap(Option_mapOrElse(None, String_defFn, String_mapFn)));

    /* ------------------------------- */

    option = Option_new(NULL);                  /* It's ok to create a option from NULL */
    (void) option;
    // assert(NULL == Option_unwrap(option));   /* but unwrapping such option will cause the program to abort. */

    return 0;
}

/*
 *
 */
OptionOf(char *) String_new(const char *literal) {
    assert(literal);
    return Option_new(strdup(literal));
}

OptionOf(char *) String_mapFn(OptionOf(char *) optionalString) {
    if (Option_isSome(optionalString)) {
        char *string = (void *) Option_unwrap(optionalString);
        return Option_new(strcpy(string, "Mapped string"));
    }

    return None;
}

OptionOf(char *) String_defFn(void) {
    return String_new("Computed string");
}