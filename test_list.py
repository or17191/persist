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
    assert ref == list(my)
    assert List(ref) == my

def test_list_creation(reference_list, my_list):
    verify_list([], List())
    verify_list(reference_list, my_list)
    assert my_list == List(my_list)

