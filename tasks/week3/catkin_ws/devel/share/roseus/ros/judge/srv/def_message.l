;; Auto-generated. Do not edit!


(when (boundp 'judge::def_message)
  (if (not (find-package "JUDGE"))
    (make-package "JUDGE"))
  (shadow 'def_message (find-package "JUDGE")))
(unless (find-package "JUDGE::DEF_MESSAGE")
  (make-package "JUDGE::DEF_MESSAGE"))
(unless (find-package "JUDGE::DEF_MESSAGEREQUEST")
  (make-package "JUDGE::DEF_MESSAGEREQUEST"))
(unless (find-package "JUDGE::DEF_MESSAGERESPONSE")
  (make-package "JUDGE::DEF_MESSAGERESPONSE"))

(in-package "ROS")





(defclass judge::def_messageRequest
  :super ros::object
  :slots (_ask ))

(defmethod judge::def_messageRequest
  (:init
   (&key
    ((:ask __ask) 0.0)
    )
   (send-super :init)
   (setq _ask (float __ask))
   self)
  (:ask
   (&optional __ask)
   (if __ask (setq _ask __ask)) _ask)
  (:serialization-length
   ()
   (+
    ;; float64 _ask
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _ask
       (sys::poke _ask (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _ask
     (setq _ask (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass judge::def_messageResponse
  :super ros::object
  :slots (_result ))

(defmethod judge::def_messageResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; int64 _result
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int64 _result
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _result (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _result) (= (length (_result . bv)) 2)) ;; bignum
              (write-long (ash (elt (_result . bv) 0) 0) s)
              (write-long (ash (elt (_result . bv) 1) -1) s))
             ((and (class _result) (= (length (_result . bv)) 1)) ;; big1
              (write-long (elt (_result . bv) 0) s)
              (write-long (if (>= _result 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _result s)(write-long (if (>= _result 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int64 _result
#+(or :alpha :irix6 :x86_64)
      (setf _result (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _result (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(defclass judge::def_message
  :super ros::object
  :slots ())

(setf (get judge::def_message :md5sum-) "42c1fb09fc6033803973422ff2802e4e")
(setf (get judge::def_message :datatype-) "judge/def_message")
(setf (get judge::def_message :request) judge::def_messageRequest)
(setf (get judge::def_message :response) judge::def_messageResponse)

(defmethod judge::def_messageRequest
  (:response () (instance judge::def_messageResponse :init)))

(setf (get judge::def_messageRequest :md5sum-) "42c1fb09fc6033803973422ff2802e4e")
(setf (get judge::def_messageRequest :datatype-) "judge/def_messageRequest")
(setf (get judge::def_messageRequest :definition-)
      "float64 ask
---
int64 result

")

(setf (get judge::def_messageResponse :md5sum-) "42c1fb09fc6033803973422ff2802e4e")
(setf (get judge::def_messageResponse :datatype-) "judge/def_messageResponse")
(setf (get judge::def_messageResponse :definition-)
      "float64 ask
---
int64 result

")



(provide :judge/def_message "42c1fb09fc6033803973422ff2802e4e")


