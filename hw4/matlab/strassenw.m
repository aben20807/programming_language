function C = strassenw(A, B, nmin)

if nargin < 3, nmin = 16; end

n = length(A);
if n ~= 2^( log2(n) )
   error('The matrix dimension must be a power of 2.')
end

if n <= nmin
%    C = A*B;
    C = zeros(n,n);
    parfor i = 1:n
        for j = 1:n
            for k = 1:n
                C(i,j) =C(i,j) + A(i,k) * B(k,j);
            end
        end
    end
else
   m = n/2; i = 1:m; j = m+1:n;

   S1 = A(j,i) + A(j,j);
   S2 = S1 - A(i,i);
   S3 = A(i,i) - A(j,i);
   S4 = A(i,j) - S2;
   S5 = B(i,j) - B(i,i);
   S6 = B(j,j) - S5;
   S7 = B(j,j) - B(i,j);
   S8 = S6 - B(j,i);

   M1 = strassenw( S2, S6, nmin);
   M2 = strassenw( A(i,i), B(i,i), nmin);
   M3 = strassenw( A(i,j), B(j,i), nmin);
   M4 = strassenw( S3, S7, nmin);
   M5 = strassenw( S1, S5, nmin);
   M6 = strassenw( S4, B(j,j), nmin);
   M7 = strassenw( A(j,j), S8, nmin);

   T1 = M1 + M2;
   T2 = T1 + M4;

   C = [ M2+M3 T1+M5+M6; T2-M7  T2+M5 ];

end