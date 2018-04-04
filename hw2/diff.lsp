(defparameter *l1* '(""))
(defparameter *l2* '(""))

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

(defun main ()
    (read-file-to-list "./file1.txt" *l1*)
    (dolist (i (reverse *l1*)) (format t "~a~%" i))
    (read-file-to-list "./file2.txt" *l2*)
    (dolist (i (reverse *l2*)) (format t "~a~%" i))
)

(main)
