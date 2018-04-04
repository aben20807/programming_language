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
            )
            (setq l (reverse l))
            (push nil l)
            (close in)
            (return-from read-file-to-list l)
        )
    )
)

(defun lcs (l1 l2)
    (let
        (
            (l1n (- (length l1) 1)) (l2n (- (length l2) 1))
        )
        (setq dp (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        (setq path (make-array (list (+ l1n 1) (+ l2n 1)) :initial-element 0))
        (loop for i from 1 to l1n
            do (loop for j from 1 to l2n
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
                do (format t "~a " (aref dp i j)) ; XXX
            )
            do (format t "~%") ; XXX
        )
        (format t "~%") ; XXX
        (let
            (
                (lcslength (aref dp l1n l2n))
                (i l1n) (j l2n) (commons nil)
                (l1pos nil) (l2pos nil) (strpos nil)
            )
            (loop while (> lcslength 0)
                do (cond
                    ((= (aref path i j) 0)
                        (push (nth i l1) commons)
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
            (push l2pos strpos)
            (push l1pos strpos)
            (return-from lcs strpos)
        )
    )
)

(defun printdiff (strpos l1 l2)
    (let
        (
            (l1n (- (length l1) 1)) (l2n (- (length l2) 1))
            (lcscurlen 0) (j 1)
            (l1pos (pop strpos))
            (l2pos (car strpos))
            ; (l2pos (pop strpos))
        )
        ; (print (nth 1 (car strpos)))
        ; (print (car strpos))
        ; (print l2pos)
        (loop for i from 1 to l1n
            ; do (loop for j from 1 to l2n
                do (cond
                    ((= i (nth lcscurlen l1pos))
                        (loop while (< j (nth lcscurlen l2pos))
                            do (format t "+~a~%" (nth j l2))
                            (incf j)
                        )
                        (format t " ~a~%" (nth i l1))
                        (incf lcscurlen)
                        (incf j)
                    )
                    ((/= i (nth lcscurlen (car strpos)))
                        (format t "-~a~%" (nth i l1))
                        ; (incf lcscurlen)
                    )
                )
            ; )
        )
    )
)

(defun main ()
    (setq *l1* (read-file-to-list "./file1.txt"))
    (dolist (i *l1*) (format t "~a~%" i)) ; XXX
    (setq *l2* (read-file-to-list "./file2.txt"))
    (dolist (i *l2*) (format t "~a~%" i)) ; XXX

    (let
        (
            (strpos (lcs *l1* *l2*))
        )
        ; (print strpos)
        (printdiff strpos *l1* *l2*)
    )
)

(main)
