// 119. Pascal's Triangle II
// Given an index k, return the k-th row of the Pascal's triangle.

// For example, given k = 3,
// Return [1,3,3,1].

// Note:
// Could you optimize your algorithm to use only O(k) extra space?
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
    int numRows = rowIndex + 1; // bug code, there's not this line before
    int **ret = (int **)malloc(sizeof(int*) * numRows);
    for (int i = 0; i < numRows; ++i)
    {
    	*(ret + i) = (int *)malloc(sizeof(int) * (i+1));
    	// *(columnSizes + i) = i + 1; // bug code
    	// *(*(columnSizes) + i) = i + 1;
    }
    
    *returnSize = numRows;

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
	// return *(ret+numRows);  // bug code
    return *(ret+numRows-1);    
}

int* getRow2(int rowIndex, int* returnSize) {
    int numRows = rowIndex + 1; // bug code, there's not this line before
    int *ret = (int *)malloc(sizeof(int) * (numRows+1));  
    *returnSize = numRows;

    for (int i = 0; i < numRows+1; ++i)
    {
    	*(ret + i) = 0;
    }

	*(ret + 0) = 1;

	for (int i = 1; i < numRows; ++i)
	{
		for (int j = i; j >= 1; --j)
		{
			*(ret + j) += *(ret + j-1);
		}
	}

    return ret;    
}