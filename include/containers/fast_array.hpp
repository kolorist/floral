namespace floral {
	template <class t_value, class t_allocator>
	void init_fixed_array(fast_fixed_array<t_value, t_allocator>& i_array, t_allocator& i_allocator)
	{
		i_array.data_allocator = &i_allocator;
		i_array.data = i_array.data_allocator->allocate_array<t_value>(i_array.capacity);
	}
}
