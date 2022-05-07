//
// Created by onerain233 on 5/6/22.
//
// unit test
#include "unittest1.h"
#include "routeFinding.h"
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


void TEST_readNode1() {
    char *normalFile = "./test/normal_nodes.txt";
    // normal file
    int cnt = readNode(normalFile);
    CU_ASSERT_EQUAL(cnt, 2);
    Node *pNode = getNodes();
    CU_ASSERT_EQUAL(pNode[0].id, -8847);
    CU_ASSERT_EQUAL(pNode[0].lat, 53.807474);
    CU_ASSERT_EQUAL(pNode[0].lon, -1.545563);
    CU_ASSERT_EQUAL(pNode[1].id, -8849);
    CU_ASSERT_EQUAL(pNode[1].lat, 53.809211);
    CU_ASSERT_EQUAL(pNode[1].lon, -1.547598);

}

void TEST_readNode2() {
    char *notExistFile = "./test/not_exist_nodes.txt";
    // not exist file
    int cnt = readNode(notExistFile);

}

void TEST_readNode3() {
    char *emptyFile = "./test/empty_nodes.txt";
    // empty file
    int cnt = readNode(emptyFile);
    CU_ASSERT_EQUAL(cnt, 0);
}

void TEST_insertEdge1() {
    readNode("./test/normal_nodes.txt");
    insertEdge(0, 1, 11.006410);
    insertEdge(1, 0, 11.006410);
    Node *pNode = getNodes();
    Node node1 = pNode[0];
    Node node2 = pNode[1];
    CU_ASSERT_EQUAL(node1.head->to, 1);
    CU_ASSERT_EQUAL(node1.head->next, NULL);
    CU_ASSERT_EQUAL(node1.head->len, 11.006410);
    CU_ASSERT_EQUAL(node2.head->to, 0);
    CU_ASSERT_EQUAL(node2.head->next, NULL);
    CU_ASSERT_EQUAL(node2.head->len, 11.006410);
}

void TEST_getNodesCnt1() {
    char *normalFile = "./test/normal_nodes.txt";
    // normal file
    int cnt = getNodesCnt(normalFile);
    CU_ASSERT_EQUAL(cnt, 2);
}

void TEST_getNodesCnt2() {
    char *notExistFile = "./test/not_exist_nodes.txt";
    // not exist file
    int cnt = getNodesCnt(notExistFile);
    CU_ASSERT_EQUAL(cnt, -1);
}

void TEST_getNodesCnt3() {
    char *emptyFile = "./test/empty_nodes.txt";
    // empty file
    int cnt = getNodesCnt(emptyFile);
    CU_ASSERT_EQUAL(cnt, 0);
}

void TEST_readLink1() {
    char *normalFile = "./test/normal_nodes.txt";
    // normal file
    int cnt = readLink(normalFile);
    CU_ASSERT_EQUAL(cnt, 1);
    Node *pNode = getNodes();

    Node node1 = pNode[0];
    Node node2 = pNode[1];
    Edge *edge1 = node1.head; // -8847
    Edge *edge2 = node2.head; // -8849

    CU_ASSERT_EQUAL(edge1->to, 1);
    CU_ASSERT_EQUAL(edge1->next, NULL);
    CU_ASSERT_EQUAL(edge1->len, 11.006410);
    CU_ASSERT_EQUAL(edge2->to, 0);
    CU_ASSERT_EQUAL(edge2->next, NULL);
    CU_ASSERT_EQUAL(edge2->len, 11.006410);
}

void TEST_readLink2() {
    char *notExistFile = "./test/not_exist_nodes.txt";
    // not exist file
    int cnt = readLink(notExistFile);
    CU_ASSERT_EQUAL(cnt, -1);
}

void TEST_dijInit1() {
    char *normalFile = "./test/normal_nodes.txt";
    // normal file
    CU_ASSERT_EQUAL(dijInit(normalFile), 1);
    CU_ASSERT_PTR_NOT_NULL(getNodes());
    CU_ASSERT_PTR_NOT_NULL(getPath());
    CU_ASSERT_PTR_NOT_NULL(getDist());
}

void TEST_dijInit2() {
    char *notExistFile = "./test/not_exist_nodes.txt";
    // not exist file
    CU_ASSERT_EQUAL(dijInit(notExistFile), -1);
}


int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "test of readNode for normal file", TEST_readNode1)) ||
        (NULL == CU_add_test(pSuite, "test of readNode for invalid file", TEST_readNode2)) ||
        (NULL == CU_add_test(pSuite, "test of readNode for empty file", TEST_readNode3)) ||
        (NULL == CU_add_test(pSuite, "test of getNodesCnt for normal file", TEST_getNodesCnt1)) ||
        (NULL == CU_add_test(pSuite, "test of getNodesCnt for invalid file", TEST_getNodesCnt2)) ||
        (NULL == CU_add_test(pSuite, "test of getNodesCnt for empty file", TEST_getNodesCnt3)) ||
        (NULL == CU_add_test(pSuite, "test of readLink for normal file", TEST_readLink1)) ||
        (NULL == CU_add_test(pSuite, "test of readLink for invalid file", TEST_readLink2)) ||
        (NULL == CU_add_test(pSuite, "test of dijInit for normal file", TEST_dijInit1)) ||
        (NULL == CU_add_test(pSuite, "test of dijInit for invalid file", TEST_dijInit2)) ||
        (NULL == CU_add_test(pSuite, "test of insertEdge", TEST_insertEdge1))) {

        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
