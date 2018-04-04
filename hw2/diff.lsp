(defparameter *ll* '(""))
(defun read-file-to-list (filename l)
    ; (let ((in1 (open "./file1.txt" :if-does-not-exist nil)))
    (let ((in1 (open filename :if-does-not-exist nil)))
          ; (in2 (open "./file2.txt" :if-does-not-exist nil)))
        (when t
            (loop for line1 = (read-line in1 nil)
                while line1
                    do (push line1 (cdr l))
                    ; do (format t "~a ~d~%" line1 (length line1)) ;and collect line1
            )
            (close in1)
            ; (close in2)
        )
    )
)

(defun print-elements-of-list (list)
    (while list
        (format t "~a~%" (car list))
        (setq list (cdr list))))

(defun main ()
    (read-file-to-list "./file1.txt" *ll*)
    ; (setq new (reverse *ll*))
    (let (( *nl* (reverse *ll*)))
        (dolist (i *nl*) (format t "~a~%" i)))
    ; (dolist (i  *ll*) (format t "~a~%" i))
    (setq *ll* '(""))
    (read-file-to-list "./file2.txt" *ll*)
    (dolist (i (reverse *ll*)) (format t "~a~%" i))
    ; (print-elements-of-list *ll*)
)
(main)
