#include "testmanager.h"


TestManager::TestManager()
{

}

void TestManager::launchAllTest()
{
    std::cout << "Launching tests sequence ... " << std::endl << std::endl;

    TestPrototype testprototype;
    testprototype.doTest();

    TestAdaptateur testadaptateur;
    testadaptateur.doTest();

    TestCommand testcommand;
    testcommand.doTest();

    TestComposite testcomposite;
    testcomposite.doTest();

    TestFabrique testfabrique;
    testfabrique.doTest();

    TestMonteur testmonteur;
    testmonteur.doTest();

    TestDecorateur testdecorateur;
    testdecorateur.doTest();

    TestChainederesponsabilite testchainederesponsabilite;
    testchainederesponsabilite.doTest();

    std::cout << std::endl << "... Ending tests sequence" << std::endl;

}
