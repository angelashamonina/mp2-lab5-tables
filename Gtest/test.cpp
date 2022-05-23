#include "pch.h"

#include"../Lab4/polinom.cpp"

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> a);
}
TEST(List, can_get_head)
{
	List<int> a;

	EXPECT_EQ(a.get_head(), nullptr);
}
TEST(List, can_get_tail)
{
	List<int> a;

	EXPECT_EQ(a.get_tail(), nullptr);
}
TEST(List, test_IsEmpty)
{
	List<int> a;

	EXPECT_EQ(a.IsEmpty(), true);
}
TEST(List, can_get_head_0_list)
{
	List<int> a;

	ASSERT_NO_THROW(a.get_head());
}
TEST(List, can_get_head_list_with_number)
{
	List<int> a;

	a.Insert(12);

	ASSERT_NO_THROW(a.get_head());
}
TEST(List, can_get_head_15list)
{
	List<int> a;

	for (int i = 1; i < 15; i++)
	{
		a.Insert(i);
	}

	ASSERT_NO_THROW(a.get_head());
}
TEST(List, can_get_prev_head_list_with_num)
{
	List<int> a;

	a.Insert(12);

	EXPECT_EQ(a.get_head()->prev, nullptr);
}
TEST(List, compare_get_prev_head_list_with_nums)
{
	List<int> a;

	for (size_t i = 1; i < 15; i++)
	{
		a.Insert(i);
	}

	EXPECT_EQ(a.get_head()->prev, nullptr);
}

TEST(Monom, can_create_monom1)
{
	ASSERT_NO_THROW(Monom m);
}
TEST(Monom, can_create_monom2)
{
	ASSERT_NO_THROW(Monom m(2, 5));
}
TEST(Monom, can_create_monom_with_big_degree)
{
	ASSERT_ANY_THROW(Monom m(2, 1100));
}
TEST(Monom, can_create_monom_with_minus_degree)
{
	ASSERT_ANY_THROW(Monom m(2, -7));
}
TEST(Monom, can_create_monom_with_0_degree)
{
	ASSERT_NO_THROW(Monom m(2, 0));
}
TEST(Monom, comparison_of_monomes1)
{
	Monom m1(5, 100);
	Monom m2(3, 300);
	EXPECT_EQ(1, m1 < m2);

}
TEST(Monom, comparison_of_monomes2)
{
	Monom m1(5, 300);
	Monom m2(3, 300);
	EXPECT_EQ(1, m1 == m2);

}
TEST(Monom, assignment_monoms)
{
	Monom m1(5, 300);
	Monom m2(3, 300);

	ASSERT_NO_THROW(m2 = m1);

}
TEST(Monom, mul_monoms)
{
	Monom m1(5, 300);
	Monom m2(3, 2);

	ASSERT_NO_THROW(m2 * m1);

}
TEST(Monom, throw_when_error_deg_monoms)
{
	Monom m1(5, 300);
	Monom m2(3, 999);

	ASSERT_ANY_THROW(m2 * m1);

}
TEST(Monom, sum_monoms)
{
	Monom m1(5, 3);
	Monom m2(3, 3);

	ASSERT_NO_THROW(m2 + m1);

}

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p);
}
TEST(Polinom, delete_monoms_with_0_cff)
{
	Polinom A;
	Polinom B;
	Monom m1(0, 1);
	Monom m2(4, 5);
	Monom m3(0, 1);
	A.polinom.Insert(m1);
	A.polinom.Insert(m2);
	A.polinom.Insert(m3);
	B.polinom.Insert(m2);
	A.simplification();
	EXPECT_EQ(B, A);
}
TEST(Polinom, do_simplification)
{
	Polinom A;
	Polinom B;
	Monom m1(4, 6);
	Monom m2(4, 6);
	Monom m3(7, 1);
	Monom m4(8, 6);
	A.polinom.Insert(m1);
	A.polinom.Insert(m2);
	A.polinom.Insert(m3);
	B.polinom.Insert(m3);
	B.polinom.Insert(m4);
	A.simplification();
	EXPECT_EQ(B, A);
}
TEST(Polinom, assignment_polinoms)
{
	Polinom A;
	Polinom B;
	Monom m1(4, 6);
	Monom m2(4, 7);
	A.polinom.Insert(m1);
	A.polinom.Insert(m2);
	A = B;

	EXPECT_EQ(B, A);
}
TEST(Polinom, sum_polinoms)
{
	Polinom A;
	Polinom B;
	Polinom t;
	Polinom D;
	Monom m1(4, 6);
	Monom m2(8, 6);
	Monom m3(8, 7);
	A.polinom.Insert(m1);
	A.polinom.Insert(m3);
	B.polinom.Insert(m2);

	t.polinom.Insert(m1);
	t.polinom.Insert(m3);
	t.polinom.Insert(m2);
	D = A + B;
	EXPECT_EQ(t, D);

}
TEST(Polinom, sub_polinoms)
{
	Polinom A;
	Polinom B;
	Polinom t;
	Polinom D;
	Monom m1(4, 6);
	Monom m2(8, 6);
	Monom m3(8, 7);
	Monom m4(-4, 6);
	A.polinom.Insert(m1);
	A.polinom.Insert(m3);
	B.polinom.Insert(m2);

	t.polinom.Insert(m4);
	t.polinom.Insert(m3);

	D = A - B;
	EXPECT_EQ(t, D);

}
TEST(Polinom, can_mul_by_const)
{
	Polinom A;
	Polinom B;
	Polinom D;
	double k = 2;
	Monom m1(3, 1);
	Monom m2(4, 5);
	Monom m3(6, 1);
	Monom m4(8, 5);
	A.polinom.Insert(m1);
	A.polinom.Insert(m2);
	B.polinom.Insert(m3);
	B.polinom.Insert(m4);
	D = A * k;
	EXPECT_EQ(B, D);
}
TEST(Polinom, can_mul_polinoms)
{
	Polinom A;
	Polinom B;
	Polinom t;
	Polinom D;
	Monom m1(3, 1);
	Monom m2(4, 5);
	Monom m3(6, 1);
	Monom m4(8, 4);
	Monom m5(18, 2);
	Monom m6(24, 5);
	Monom m7(24, 6);
	Monom m8(32, 9);
	A.polinom.Insert(m1);
	A.polinom.Insert(m2);
	B.polinom.Insert(m3);
	B.polinom.Insert(m4);
	t.polinom.Insert(m5);
	t.polinom.Insert(m6);
	t.polinom.Insert(m7);
	t.polinom.Insert(m8);

	D = A * B;
	EXPECT_EQ(t, D);
}
TEST(Polinom, throw_when_error_degree_in_mul)
{
	Polinom A;
	Polinom B;

	Monom m1(3, 1);
	Monom m2(4, 55);
	Monom m3(6, 1);
	Monom m4(8, 5);

	A.polinom.Insert(m1);
	A.polinom.Insert(m2);
	B.polinom.Insert(m3);
	B.polinom.Insert(m4);


	ASSERT_ANY_THROW(A * B);
}

TEST(RBTree, can_insert_in_tree)
{
	RBTree<int, int> tree;
	ASSERT_NO_THROW(tree.insert(1, 1));
}
TEST(RBTree, can_del_in_tree)
{
	RBTree<int, int> tree;
	tree.insert(1, 1);
	ASSERT_NO_THROW(tree.remove(1));
}
TEST(RBTree, can_search_in_tree)
{
	RBTree<int, int> tree;
	tree.insert(1, 1);
	EXPECT_EQ(tree.search(1)->data,1);
}

TEST(Hash, can_insert_in_Hash)
{
	Hash<int>* hash = new Hash<int>;
	ASSERT_NO_THROW(hash->insertNode("1", 1));
}
TEST(Hash, can_del_in_Hash)
{
	Hash<int>* hash = new Hash<int>;
	hash->insertNode("1", 1);
	ASSERT_NO_THROW(hash->deleteNode("1"););
}
TEST(Hash, can_search_in_Hash)
{
	Hash<int>* hash = new Hash<int>;
	hash->insertNode("1", 1);
	EXPECT_EQ(hash->search("1")->data, 1);
}

TEST(Table, can_insert_in_Table)
{
	Table <int> table;
	ASSERT_NO_THROW(table.insert("1", 1));
}
TEST(Table, can_del_in_Table)
{
	Table <int>table;
	table.insert("1", 1);
	ASSERT_NO_THROW(table.del("1"));
}
TEST(Table, can_search_in_Table)
{
	Table <int>table;
	table.insert("1", 1);
	EXPECT_EQ(table.search("1"), 1);
}