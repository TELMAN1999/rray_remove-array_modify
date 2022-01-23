#include <iostream>
#include <cassert>

class array
{
public:
    typedef int element_type;
    typedef unsigned int size_type;

public:
    size_type size() const;
    bool empty() const;
    element_type access(size_type index) const;
    void modify(size_type index, const element_type& value);
    void insert(size_type index, const element_type& value);
    void remove(size_type index);
private:
	element_type* m_start;
	size_type m_size;

public:
    array();
    array(size_type n, const element_type& default_value);
    array(const array& b);
    const array& operator=(const array& c);
    ~array();
};

array::size_type array::size() const
{
	return m_size;
}

array::array()
{
    std::cout << "Default constructor" << std::endl;
	m_size = 0;
	m_start = nullptr;
}

array::array(const array& b)
{
    std::cout << "Copy Constructor" << std::endl;
    m_size = b.m_size;
    if (m_size == 0) {
        m_start = nullptr;
    } else {
        m_start = new element_type[m_size];
        for (size_type i = 0; i < m_size; ++i) {
            m_start[i] = b.m_start[i];
        }
    }
}

const array& array::operator=(const array& c)
{
    assert(c.m_size >= 0);
    if (this == &c) {
        return *this;
    }
    std::cout << "Assignment Operator" << std::endl;
    if (m_start != nullptr) {
        delete [] m_start;
        m_start = nullptr;
    }
    assert(m_start == nullptr);
    m_size = c.m_size;
    if (m_size > 0) {
        m_start = new element_type[m_size];
        for (size_type i = 0; i < m_size; ++i) {
            m_start[i] = c.m_start[i];
        }
    }
    return *this;
}

array::array(size_type n, const element_type& default_value)
{
    std::cout << "Constructor" << std::endl;
	m_size = 0;
	m_size = n;
	m_start = new element_type[n];
	for (size_type i = 0; i < m_size; ++i) {
		m_start[i] = default_value;
	}
}

array::~array()
{
    std::cout << "Destructor" << std::endl;
    if (m_start != nullptr) {
        delete [] m_start;
    }
}

void array::insert(size_type index, const element_type& value)
{
	assert(index >= 0);
	assert(index <= m_size);
	m_size = m_size + 1;
	element_type* tmp = new element_type[m_size];
	for (size_type i = 0; i < index; ++i) {
		tmp[i] = m_start[i];
	}
	tmp[index] = value;
	for (size_type i = index + 1; i < m_size; ++i) {
		tmp[i] = m_start[i - 1];
	}
    if (m_start != nullptr) {
        delete [] m_start;
    }
	m_start = tmp;
}

bool array::empty() const
{
    assert(m_size >= 0);
	return m_size == 0;
}

array::element_type array::access(array::size_type index) const
{
	assert(index >= 0);
	assert(index < m_size);
    assert(m_start != nullptr);
	return m_start[index];
}

void array::modify(size_type index, const element_type& value)
{
	assert(index >= 0);
	assert(index < m_size);
	m_start[index] = value;
}
void array::remove(size_type index)
{
        assert(index >= 0);
        assert(index < m_size);
        m_size = m_size - 1;
        element_type* tmp = new element_type[m_size];
        for (size_type i = 0; i < index; ++i) {
                tmp[i] = m_start[i];
        }
        for (size_type i = index; i < m_size; ++i) {
                tmp[i] = m_start[i + 1];
        }
        if (m_start != nullptr) {
                delete [] m_start;
        }
        m_start = tmp;
}


void test_1()
{
    array a(4, 0);
    assert(a.size() == 4);
    assert(! a.empty());
    assert(a.access(0) == 0);
    assert(a.access(1) == 0);
    assert(a.access(2) == 0);
    assert(a.access(3) == 0);
	a.insert(a.size(), 8);
	a.insert(a.size(), 9);
    assert(a.size() == 6);
    assert(a.access(0) == 0);
    assert(a.access(1) == 0);
    assert(a.access(2) == 0);
    assert(a.access(3) == 0);
    assert(a.access(4) == 8);
    assert(a.access(5) == 9);
	a.insert(0, 5);
    assert(a.size() == 7);
    assert(a.access(0) == 5);
    assert(a.access(1) == 0);
    assert(a.access(2) == 0);
    assert(a.access(3) == 0);
    assert(a.access(4) == 0);
    assert(a.access(5) == 8);
    assert(a.access(6) == 9);
	a.insert(5, 15);
    assert(a.size() == 8);
    assert(a.access(0) == 5);
    assert(a.access(1) == 0);
    assert(a.access(2) == 0);
    assert(a.access(3) == 0);
    assert(a.access(4) == 0);
    assert(a.access(5) == 15);
    assert(a.access(6) == 8);
    assert(a.access(7) == 9);
	for (array::size_type i = 0; i < a.size(); ++i)  {
        std::cout << "a[" << i << "]" << a.access(i) << std::endl;
	}
}

void test_2()
{
	array b;
    assert(b.size() == 0);
    assert(b.empty());
}

void test_3()
{
	array* c = new array(5, 8);
    assert(c->size() == 5);
    assert((*c).size() == 5);
    assert(! c->empty());
	delete c;
}

void test_4()
{
	array* d = new array[5];
    assert(d[0].size() == 0);
    assert(d[1].size() == 0);
    assert(d[2].size() == 0);
    assert(d[3].size() == 0);
    assert(d[4].size() == 0);
    for (int i = 0; i < 5; ++i) {
        assert(d[i].empty());
    }
	delete [] d;
}

void test_copy()
{
	array b(5, 0);
    assert(b.size() == 5);
    for (array::size_type i = 0; i < b.size(); ++i) {
        b.modify(i, 2 * i);
    }
    assert(b.access(0) == 0);
    assert(b.access(1) == 2);
    assert(b.access(2) == 4);
    assert(b.access(3) == 6);
    assert(b.access(4) == 8);
    array c(b);
    assert(c.size() == 5);
    assert(c.access(0) == 0);
    assert(c.access(1) == 2);
    assert(c.access(2) == 4);
    assert(c.access(3) == 6);
    assert(c.access(4) == 8);
}

void test_copy_on_empty()
{
	array b;
    assert(b.size() == 0);
    assert(b.empty());
    array c(b);
    assert(c.size() == 0);
    assert(c.empty());
}

void test_assignment_on_empty()
{
	array b;
    assert(b.empty());
    array c(4, 0);
    assert(c.size() == 4);
    b = c; // b.operator=(c);
    assert(b.size() == 4);
    assert(b.access(0) == 0);
    assert(b.access(1) == 0);
    assert(b.access(2) == 0);
    assert(b.access(3) == 0);
}

void test_assignment()
{
	array b(16, 1);
    assert(b.size() == 16);
    array c(4, 0);
    assert(c.size() == 4);
    b = c; // b.operator=(c);
    assert(b.size() == 4);
    assert(b.access(0) == 0);
    assert(b.access(1) == 0);
    assert(b.access(2) == 0);
    assert(b.access(3) == 0);
}

void test_multiple_assignemnts()
{
	array a(1, 1);
    assert(a.size() == 1);
	array b(2, 2);
    assert(b.size() == 2);
	array c(3, 3);
    assert(c.size() == 3);
    a = b = c;
    assert(b.size() == 3);
    assert(b.access(0) == 3);
    assert(b.access(1) == 3);
    assert(b.access(2) == 3);
    assert(a.size() == 3);
    assert(a.access(0) == 3);
    assert(a.access(1) == 3);
    assert(a.access(2) == 3);
    assert(c.size() == 3);
    assert(c.access(0) == 3);
    assert(c.access(1) == 3);
    assert(c.access(2) == 3);
    a = a;
}

void test_modify()
{
        array sample(4,0);
        array::element_type old_value = sample.access(2);
        sample.modify(2,10);
        array::element_type new_value = sample.access(2);
        std::cout << "Modify" << std::endl;
}

void test_remove()
{
        array sample(10,1);
        for (array::size_type i = 0; i < sample.size(); ++i) sample.modify(i,2*i);
        array::element_type preremoved_value = sample.access(4);
        array::size_type preremoved_size = sample.size();
        sample.remove(4);
        array::size_type after_remove_size = sample.size();
        array::element_type after_remove_value = sample.access(4);
        std::cout << "Remove" << std::endl;
}



int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
   // est_copy();
    test_copy_on_empty();
    test_assignment();
    test_assignment_on_empty();
    test_multiple_assignemnts();
    test_remove();
    test_modify();
	return 0;
}
