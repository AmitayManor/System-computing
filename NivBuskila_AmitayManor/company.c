#include "company.h"
#include <stdlib.h>
#include <stdio.h>

// Assuming the existence of create_interstellar_travel and free_interstellar_travel functions

void free_company(Company* company) {
    if (company) {
        free(company->name);
        for (int i = 0; i < company->numTravels; i++) {
            free_interstellar_travel(company->travels[i]); // Assumes a free_interstellar_travel function exists
        }
        free(company->travels);
        free(company);
    }
}
