#!/usr/bin/env python3

import pytest
from pyrsist import List

@pytest.fixture
def reference_list():
    return [1, 2, 3, 4, 5]

@pytest.fixture
def my_list(reference_list):
    return List(reference_list)

def verify_list(ref, my):
    assert len(ref) == len(my)
    assert all(r == m for r, m in zip(ref, my))
    assert ref == type(ref)(my)
    assert type(my)(ref) == my

def test_list_creation(reference_list, my_list):
    verify_list([], List())
    verify_list(reference_list, my_list)
    assert my_list == List(my_list)

def test_list_repr(reference_list, my_list):
    assert repr(my_list) == 'List({!r})'.format(reference_list)

def test_complex_list():
    ref_lst = [list(range(i)) for i in range(5)]
    my_lst = List(list(range(i)) for i in range(5))
    verify_list(ref_lst, my_lst)

