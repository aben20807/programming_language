(defun read-file-to-list (filename)
    ;; Open a file by the argument and read it line by line into a list
    ;; whose first element is a nil. For example:
    ;; File contents of file1.txt are following
    ;; abc
    ;; def
    ;; When you call read-file-to-list with "./file1.txt" as the argument,
    ;; it will return a list: (nil, "abc", "def").
    (let
        (
            (in (open filename :if-does-not-exist nil))
            (l nil)
        )
        (when in
            (loop for line = (read-line in nil)
                while line
                    do (push line l)
            )
            (setq l (reverse l))
            (push nil l)
            (close in)
            (return-from read-file-to-list l)
        )
    )
)

(defun lcs (l1 l2)
    ;; Find out longest common subsequence from two lists l1 and l2
    ;; and return these subsequence position of each lists.
    (let
        (
            (l1n (- (length l1) 1)) (l2n (- (length l2) 1))
            (dp nil) (path nil)
        )
        (setq dp (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        (setq path (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
                do (cond
                    ((string= (nth i l1) (nth j l2))
                        (setf (aref dp i j)
                            (+ (aref dp (- i 1) (- j 1)) 1)
                        )
                        (setf (aref path i j) 0)
                    )
                    ((< (aref dp (- i 1) j) (aref dp i (- j 1)))
                        (setf (aref dp i j)
                            (aref dp i (- j 1))
                        )
                        (setf (aref path i j) 1)
                    )
                    ((>= (aref dp (- i 1) j) (aref dp i (- j 1)))
                        (setf (aref dp i j)
                            (aref dp (- i 1) j)
                        )
                        (setf (aref path i j) 2)
                    )
                )
            )
        )
        #| ; DEBUG print dp and path
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
                do (cond
                    ((= (aref path i j) 0)
                        (format t "↖"))
                    ((= (aref path i j) 1)
                        (format t "←"))
                    ((= (aref path i j) 2)
                        (format t "↑"))
                )
                do (format t "~a " (aref dp i j))
            )
            do (format t "~%")
        )
        (format t "~%")
        |# ;
        (let
            (
                (lcslength (aref dp l1n l2n))
                (i l1n) (j l2n)
                (l1pos nil) (l2pos nil)
            )
            (loop while (> lcslength 0)
                ;; Go through the path reversely.
                do (cond
                    ((= (aref path i j) 0)
                        (push i l1pos)
                        (push j l2pos)
                        (decf lcslength)
                        (decf i)
                        (decf j)
                    )
                    ((= (aref path i j) 1)
                        (decf j)
                    )
                    ((= (aref path i j) 2)
                        (decf i)
                    )
                )
            )
            (return-from lcs (values l1pos l2pos))
        )
    )
)

(defun printdiff (l1pos l2pos l1 l2)
    ;; Print out the diff result by two lists l1 and l2 and two arrays l1pos
    ;; and l2pos.
    (let
        (
            (l1n (- (length l1) 1)) (l2n (- (length l2) 1))
            (lcscurlen 0) (i 1) (j 1)
        )
        (loop while (<= i l1n)
            do (cond
                ((< lcscurlen (length l1pos))
                    (cond
                        ((= i (nth lcscurlen l1pos))
                            (loop while (< j (nth lcscurlen l2pos))
                                do (format t "~C[32m+~a~%~C[00m"
                                    #\ESC (nth j l2) #\ESC)
                                do (incf j)
                            )
                            (format t " ~a~%" (nth i l1))
                            (incf lcscurlen)
                            (incf j)
                        )
                        ((/= i (nth lcscurlen l1pos))
                            (format t "~C[31m-~a~%~C[00m"
                            #\ESC (nth i l1) #\ESC)
                        )
                    )
                )
                ((>= lcscurlen (length l1pos))
                    (return)
                )
            )
            do (incf i)
        )
        (loop while (<= i l1n)
            do (format t "~C[31m-~a~%~C[00m" #\ESC (nth i l1) #\ESC)
            do (incf i)
        )
        (loop while (<= j l2n)
            do (format t "~C[32m+~a~%~C[00m" #\ESC (nth j l2) #\ESC)
            do (incf j)
        )
    )
)

(defun main ()
    ;; In main function, get two lists from files and print diff result
    ;; after finding their longest common subsequence.
    (let
        (
            (l1 (read-file-to-list "./file1.txt"))
            (l2 (read-file-to-list "./file2.txt"))
        )
        ; (dolist (i l1) (format t "~a~%" i)) ; DEBUG
        ; (dolist (i l2) (format t "~a~%" i)) ; DEBUG
        (multiple-value-bind (l1pos l2pos) (lcs l1 l2)
            (printdiff l1pos l2pos l1 l2)
        )
    )
)

(main)
