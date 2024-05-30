#include <gtest.h>
#include "AVL_tree.h"
#include "unordered_table.h"
#include "ordered_table.h"
#include "hash_table.h"

//tests for avl-tree

TEST(AVLtree, can_create_table) {
	ASSERT_NO_THROW(AVLtree T);
}
TEST(AVLtree, can_copy_table) {
	AVLtree T;
	ASSERT_NO_THROW(AVLtree T1(T));
}
TEST(AVLtree, can_add_an_element) {
	AVLtree T;
	ASSERT_NO_THROW(T.addPol("pol", Polinom("1+x+x^2")););
}
TEST(AVLtree, can_find_an_element) {
	string str = "pol";
	AVLtree T;
	T.addPol("pol", Polinom("1+x+x^2"));
	ASSERT_NO_THROW(T.searchPol(str));
}
TEST(AVLtree, can_clear) {
	AVLtree T;
	T.addPol("pol", Polinom("1+x+x^2"));
	ASSERT_NO_THROW(T.delPol("pol"));
}
TEST(AVLtree, clear_is_correct) {
	string str = "pol";
	AVLtree T;
	T.addPol("pol", Polinom("1+x+x^2"));
	T.delPol("pol");
	EXPECT_EQ(nullptr, T.searchPol(str));
}

//test for ordered table
TEST(OrderedTable, can_add_an_element) {
	OrderedTable T;
	ASSERT_NO_THROW(T.addPol("pol", Polinom("1+x+x^2")));
}

TEST(OrderedTable, can_find_an_element) {
	OrderedTable T;
	T.addPol("pol", Polinom("1+x+x^2"));
	ASSERT_NO_THROW(T.searchPol("pol"));
}

TEST(OrderedTable, can_delete_element) {
	OrderedTable T;
	Polinom p = Polinom("1+x+x^2");
	T.addPol("pol", p);
	ASSERT_NO_THROW(T.delPol("pol"));
}

TEST(OrderedTable, delete_is_correct) {
	OrderedTable T;
	Polinom p = Polinom("1+x+x^2");
	T.addPol("pol", p);
	T.delPol("pol");
	EXPECT_EQ(nullptr, T.searchPol("pol"));
}

//tests for unordered tables

TEST(UnorderedTable, can_add_an_element) {
	UnorderedTable T;
	ASSERT_NO_THROW(T.addPol("pol", Polinom("1+x+x^2")));
}

TEST(UnorderedTable, can_find_an_element) {
	UnorderedTable T;
	T.addPol("pol", Polinom("1+x+x^2"));
	ASSERT_NO_THROW(T.searchPol("pol"));
}

TEST(UnorderedTable, can_delete_element) {
	UnorderedTable T;
	Polinom p = Polinom("1+x+x^2");
	T.addPol("pol", p);
	ASSERT_NO_THROW(T.delPol("pol"));
}

TEST(UnorderedTable, delete_is_correct) {
	UnorderedTable T;
	Polinom p = Polinom("1+x+x^2");
	T.addPol("pol", p);
	T.delPol("pol");
	EXPECT_EQ(nullptr, T.searchPol("pol"));
}

//tests for hash tables
TEST(HashTable, can_create_hash_table) {
	ASSERT_NO_THROW(HashTable<HashFunc1> T);
}

TEST(HashTable, can_add_an_element) {
	HashTable<HashFunc1> T;
	ASSERT_NO_THROW(T.addPol("pol", Polinom("1+x+x^2")));
}

TEST(HashTable, can_find_an_element) {
	HashTable<HashFunc1> T;
	T.addPol("pol", Polinom("1+x+x^2"));
	ASSERT_NO_THROW(T.searchPol("pol"));
}

TEST(HashTable, return_nullptr_when_cant_find_an_element) {
	HashTable<HashFunc1> T;
	EXPECT_EQ(nullptr, T.searchPol("pol"));
}

TEST(HashTable, can_delete) {
	HashTable<HashFunc1> T;
	Polinom p = Polinom("1+x+x^2");
	T.addPol("pol", p);
	ASSERT_NO_THROW(T.delPol("pol"));
}

TEST(HashTable, delete_is_correct) {
	HashTable<HashFunc1> T;
	Polinom p = Polinom("1+x+x^2");
	T.addPol("pol", p);
	T.delPol("pol");
	EXPECT_EQ(nullptr, T.searchPol("pol"));
}