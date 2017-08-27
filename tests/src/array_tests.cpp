#include <catch.hpp>

#include <floral.h>

class MemoryEnvFixture {
	protected:
		class GenericAllocator {
			public:
				template <class DType>
				DType* AllocateArray(const u32 elemNum)
				{
					return new DType[elemNum];
				}
				void Free(voidptr pData)
				{
					delete[] pData;
				}
		};

	protected:
		GenericAllocator						FixtureAllocator;
};

TEST_CASE_METHOD(MemoryEnvFixture, "fixed_array", "fixed_array") {
	using namespace floral;

	fixed_array<s32, GenericAllocator> arr1(3, &FixtureAllocator);
	arr1.PushBack(1);
	arr1.PushBack(2);
	arr1.PushBack(3);

	REQUIRE(arr1[0] == 1);
	REQUIRE(arr1[1] == 2);
	REQUIRE(arr1[2] == 3);
	REQUIRE_THROWS_WITH( arr1.PushBack(4), "Not enough array memory for PushBack" );
};

TEST_CASE_METHOD(MemoryEnvFixture, "dynamic_array", "dynamic_array") {
	using namespace floral;

	dynamic_array<s32, GenericAllocator> arr1(3, &FixtureAllocator);
	arr1.PushBack(1);
	arr1.PushBack(2);
	arr1.PushBack(3);

	REQUIRE(arr1[0] == 1);
	REQUIRE(arr1[1] == 2);
	REQUIRE(arr1[2] == 3);
	REQUIRE_NOTHROW( arr1.PushBack(4) );
};
