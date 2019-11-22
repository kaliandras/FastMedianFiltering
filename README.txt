Algorithm Description for median filtering:
(https://ieeexplore.ieee.org/document/808571/)
	Input: NxN matrix
	Output: median of the matrix
	Variables:
		N - size of the square matrix (in this implementation assumed to be 5)
		M - (N-1)/2
		k - slope of a diagonal
		r - row number
		c - column number

	1. Sort columns in an ascending order.
	2. Sort rows in an ascending order.
		Its not necessary to sort all elements in every row, only thjose elements need tob e sorted that will be used later.
	3. Sort diagonals in an ascending order. Diagonals are defined by s and k.
		s=k*r+c where k=1...M and s=k(*M+1)...k(*M-1)+N-1
	4. Median is the c=M r=M component.

Plain c implementation.
	This implementation is created as a reference model, so acceleration can be measured with different implementations.
	It loads and saves an image with the DevIL library, the image is passed through the img_filter() function. 
	It will step through the image, while it separates color channels and creates matrices for the filtering. 
	The filtering is preformed for every color channel, separatly with the median_filter() function.
