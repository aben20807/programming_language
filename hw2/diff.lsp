(defparameter *l1* '(nil))
(defparameter *l2* '(nil))
(defvar dp)

(defun read-file-to-list (filename l)
    (let ((in (open filename :if-does-not-exist nil)))
        (when in
            (loop for line = (read-line in nil)
                while line
                    do (push line (cdr l))
                    ; do (format t "~a ~d~%" line (length line))
            )
            (close in)
        )
    )
)

(defun lcs (l1 l2)
    (let ((l1n (- (length l1) 1)) (l2n (- (length l2) 1)))
        (setq dp (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
                do (if (string= (nth i *l1*) (nth j *l2*))
                    (setf (aref dp i j)
                        (+ (aref dp (- i 1) (- j 1)) 1))
                    (setf (aref dp i j)
                        (max (aref dp (- i 1) j)(aref dp i (- j 1)))
                    )
                )
            )
        )
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
                do (format t "~a" (aref dp i j))
            )
            do (format t "~%")
        )
    )
)

(defun main ()
    (read-file-to-list "./file1.txt" *l1*)
    (dolist (i (reverse *l1*)) (format t "~a~%" i))
    (read-file-to-list "./file2.txt" *l2*)
    (dolist (i (reverse *l2*)) (format t "~a~%" i))

    (lcs *l1* *l2*)

)

(main)
