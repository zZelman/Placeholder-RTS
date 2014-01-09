#ifndef SROOMBOOKKEEPING_H_
#define SROOMBOOKKEEPING_H_

/**
 * A template struct containing data fields for ALL room types.
 */
template <typename T>
struct SRoomBookkeeping
{
	T debug;
	T warehouse;
	T kitchen;
	T smithy;
	T powerPlant;
	T warSpawner;
	T researchSpawner;
	T supportSpawner;

	/**
	 * Expects that <T> is a pointer and deletes it, then NULLs it.
	 */
	inline void data_delete()
	{
		delete debug;
		delete warehouse;
		delete kitchen;
		delete smithy;
		delete powerPlant;
		delete warSpawner;
		delete researchSpawner;
		delete supportSpawner;
	}

	/**
	 * Sets all data fields to 0.
	 */
	inline void data_null()
	{
		int val = 0;

		warehouse 			= val;
		kitchen 			= val;
		smithy 				= val;
		powerPlant 			= val;
		warSpawner 			= val;
		researchSpawner 	= val;
		supportSpawner		= val;

	}

	/**
	 * Expects that <T> is a bool, and sets it to false.
	 */
	inline void data_false()
	{
		bool val = false;

		warehouse 			= val;
		kitchen 			= val;
		smithy 				= val;
		powerPlant 			= val;
		warSpawner 			= val;
		researchSpawner 	= val;
		supportSpawner		= val;
	}
};


#endif /* TEMPLATES_H_ */
