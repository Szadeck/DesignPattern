#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include "prototype.h"
#include "adaptateur.h"
#include "commande.h"
#include "composite.h"
#include "fabrique.h"
#include "monteur.h"
#include "decorateur.h"
#include "chainederesponsabilite.h"

class TestManager
{
public:
    TestManager();
    void launchAllTest();
};

#endif // TESTMANAGER_H
