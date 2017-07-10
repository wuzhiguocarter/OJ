// 118. Pascal's Triangle
// Given numRows, generate the first numRows of Pascal's triangle.

// For example, given numRows = 5,
// Return

// [
//      [1],
//     [1,1],
//    [1,2,1],
//   [1,3,3,1],
//  [1,4,6,4,1]
// ]
/**
 * Return an array of arrays.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 * assume caller calls free().
 */
int** generate(int numRows, int** columnSizes) {
    *columnSizes = (int *)malloc(sizeof(int) * numRows);
    int **ret = (int **)malloc(sizeof(int*) * numRows);
    for (int i = 0; i < numRows; ++i)
    {
    	*(ret + i) = (int *)malloc(sizeof(int) * (i+1));
    	// *(columnSizes + i) = i + 1; // bug code
    	*(*(columnSizes) + i) = i + 1;
    }
    if (numRows > 0)
    {
    	**ret = 1;

    	if (numRows > 1)
    	{
			*(*(ret + 1) ) = 1;
			*(*(ret + 1) + 1) = 1;

			if (numRows > 2)
			{
				for (int i = 2; i < numRows; ++i)
				{
					*(*(ret + i)) = 1;
					*(*(ret + i) + i) = 1;
					for (int j = 1; j <= i-1; ++j)
					{
						*(*(ret + i) + j) = *(*(ret + i-1) + j-1) + *(*(ret + i-1) + j);
					}
				}
			}

	    }
	}

    return ret;
}