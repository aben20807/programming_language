(defparameter *ll* '(""))
(defun read-file ()
    (let ((in1 (open "./file1.txt" :if-does-not-exist nil))
          (in2 (open "./file2.txt" :if-does-not-exist nil)))
        (when t
            (loop for line1 = (read-line in1 nil)
                ; when (> (length line1) 0)
                while line1
                ; do (progn
                ; do (format t "~a ~d~%" line1 (length line1)) ;and collect line1
                do (push line1 (cdr *ll*)
                ; collect line1
                )
            )
            ; (loop for line1 = (read-line in2 nil)
                ; while line1
                ; do (format t "~a ~d~%" line1 (length line1))
            ; )
            (close in1)
            (close in2)
        )
    )
)

(defun print-elements-of-list (list)
    (while list
        (format t "~a~%" (car list))
        (setq list (cdr list))))

(defun main ()
    (read-file)
    ; (setq new (reverse *ll*))
    (let (( *nl* (reverse *ll*)))
        (dolist (i *nl*) (format t "~a~%" i)))
    ; (dolist (i  *ll*) (format t "~a~%" i))
    (dolist (i (reverse *ll*)) (format t "~a~%" i))
    ; (print-elements-of-list *ll*)
)
(main)
