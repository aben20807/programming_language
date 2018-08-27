function C = par_loop(A,B)
    disp('For loop with parallel')
    n = length(A);
    C = zeros(n,n);
    tic
    parfor i = 1:n
        for j = 1:n
            for k = 1:n
                C(i,j) = C(i,j) + A(i,k) * B(k,j);
            end
        end
    end
    toc
end