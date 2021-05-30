#include "locale.h"

#include "stdlib.h"
#include "string.h"

locale_t duplocale(locale_t baselocale) {
    locale_t newlocale = (locale_t) malloc(sizeof(struct lconv));
    memcpy(newlocale, baselocale, sizeof(struct lconv));

    newlocale->currency_symbol   = strdup(baselocale->currency_symbol);
    newlocale->decimal_point     = strdup(baselocale->decimal_point);
    newlocale->grouping          = strdup(baselocale->grouping);
    newlocale->int_curr_symbol   = strdup(baselocale->int_curr_symbol);
    newlocale->mon_decimal_point = strdup(baselocale->mon_decimal_point);
    newlocale->mon_grouping      = strdup(baselocale->mon_grouping);
    newlocale->mon_thousands_sep = strdup(baselocale->mon_thousands_sep);
    newlocale->negative_sign     = strdup(baselocale->negative_sign);
    newlocale->positive_sign     = strdup(baselocale->positive_sign);
    newlocale->thousands_sep     = strdup(baselocale->thousands_sep);

    return newlocale;
}

void freelocale(locale_t locale) {
    free(locale->currency_symbol);
    free(locale->decimal_point);
    free(locale->grouping);
    free(locale->int_curr_symbol);
    free(locale->mon_decimal_point);
    free(locale->mon_grouping);
    free(locale->mon_thousands_sep);
    free(locale->negative_sign);
    free(locale->positive_sign);
    free(locale->thousands_sep);
    free(locale);
}

struct lconv* localeconv() {}