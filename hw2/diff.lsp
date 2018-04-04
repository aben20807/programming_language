(defvar *l1*)
(defvar *l2*)
(defvar dp)
(defvar path)

(defun read-file-to-list (filename)
    (let
        (
            (in (open filename :if-does-not-exist nil))
            (l nil)
        )
        (when in
            (loop for line = (read-line in nil)
                while line
                    do (push line l)
                    ; do (format t "~a ~d~%" line (length line))
            )
            (setq l (reverse l))
            (push nil l)
            ; (print l)
            (close in)
            (return-from read-file-to-list l)
        )
    )
)

(defun lcs (l1 l2)
    (let
        (
            (l1n (- (length l1) 1)) (l2n (- (length l2) 1))
            ; (rl1 (reverse l1)) (rl2 (reverse l2))
        )
        (setq dp (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        (setq path (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        ; (print rl1)
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
                    ; do(format t "~a~%" (nth i rl1))
                do (cond
                    ((string= (nth i l1) (nth j l2))
                        (setf (aref dp i j)
                            (+ (aref dp (- i 1) (- j 1)) 1) ; dp[i-1][j-1]+1
                        )
                        (setf (aref path i j) 0)
                        ; (format t "~a~%" (nth i l1))
                    )
                    ((< (aref dp (- i 1) j) (aref dp i (- j 1)))
                        (setf (aref dp i j)
                            (aref dp i (- j 1))
                        )
                        (setf (aref path i j) 1)
                        ; (format t "~a~%" (nth i rl1))
                    )
                    ((>= (aref dp (- i 1) j) (aref dp i (- j 1)))
                        (setf (aref dp i j)
                            (aref dp (- i 1) j)
                        )
                        (setf (aref path i j) 2)
                        ; (format t "~a~%" (nth i rl1))
                    )
                )
            )
        )
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
                do (cond
                    ((= (aref path i j) 0)
                        (format t "↖")
                    )
                    ((= (aref path i j) 1)
                        (format t "←")
                    )
                    ((= (aref path i j) 2)
                        (format t "↑")
                    )
                )
                do (format t "~a " (aref dp i j))
            )
            do (format t "~%")
        )
    )
)

(defun main ()
    (setq *l1* (read-file-to-list "./file1.txt"))
    (dolist (i *l1*) (format t "~a~%" i))
    (setq *l2* (read-file-to-list "./file2.txt"))
    (dolist (i *l2*) (format t "~a~%" i))

    (lcs *l1* *l2*)

)

(main)
