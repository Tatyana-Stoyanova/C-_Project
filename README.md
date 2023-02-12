# Cpp_Project

The goal of the project is to create a pseudo dynamic structure that works like list, but can be indexed like an array. The structure can be resized, but not by creating a new array twice bigger than the old array, storing in it the already added values from the old one, when the old one runs out of space and deleting the old one. To achieve this, I have created a class dynamicArray that is actually an array to array to integer. The class DynamicArrayList represents actually an list of dynamicArrays.
