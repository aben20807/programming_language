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

(defun lcs (l1 l2)
    (loop for i in l1
        ; do (print i)
    )
    ; (print (length l1))
    ; (print (length l2))
    ; (setq myarray (make-array '(2 2); ((length l1) (length l2))
        ; :initial-element '0
        ; :adjustable t
    ; ))
    ; (write myarray)
    ; (terpri)
    ; (setq l1n '(length l1))
    (write
        (make-array (list (length l1) (length l2)) :initial-element 0)
    )
    ; (let ((l1n (length l1) (l2n (length l2))))
    ; (write (make-array '(l1n l2n) :initial-element 0))
    ; (terpri)
    ; )
)

(defun main ()
    (read-file-to-list "./file1.txt" *l1*)
    (dolist (i (reverse *l1*)) (format t "~a~%" i))
    (read-file-to-list "./file2.txt" *l2*)
    (dolist (i (reverse *l2*)) (format t "~a~%" i))

    ; (dolist (i (reverse *l1*))
        ; (dolist (j (reverse *l2*)) (format t "~a~%" (string= i j))); (print (string= i j))
    ; )
    (lcs *l1* *l2*)
)

(main)
