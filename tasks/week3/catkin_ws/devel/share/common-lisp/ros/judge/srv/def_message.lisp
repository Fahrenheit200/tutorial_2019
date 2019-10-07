; Auto-generated. Do not edit!


(cl:in-package judge-srv)


;//! \htmlinclude def_message-request.msg.html

(cl:defclass <def_message-request> (roslisp-msg-protocol:ros-message)
  ((ask
    :reader ask
    :initarg :ask
    :type cl:float
    :initform 0.0))
)

(cl:defclass def_message-request (<def_message-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <def_message-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'def_message-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name judge-srv:<def_message-request> is deprecated: use judge-srv:def_message-request instead.")))

(cl:ensure-generic-function 'ask-val :lambda-list '(m))
(cl:defmethod ask-val ((m <def_message-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader judge-srv:ask-val is deprecated.  Use judge-srv:ask instead.")
  (ask m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <def_message-request>) ostream)
  "Serializes a message object of type '<def_message-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ask))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <def_message-request>) istream)
  "Deserializes a message object of type '<def_message-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ask) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<def_message-request>)))
  "Returns string type for a service object of type '<def_message-request>"
  "judge/def_messageRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'def_message-request)))
  "Returns string type for a service object of type 'def_message-request"
  "judge/def_messageRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<def_message-request>)))
  "Returns md5sum for a message object of type '<def_message-request>"
  "42c1fb09fc6033803973422ff2802e4e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'def_message-request)))
  "Returns md5sum for a message object of type 'def_message-request"
  "42c1fb09fc6033803973422ff2802e4e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<def_message-request>)))
  "Returns full string definition for message of type '<def_message-request>"
  (cl:format cl:nil "float64 ask~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'def_message-request)))
  "Returns full string definition for message of type 'def_message-request"
  (cl:format cl:nil "float64 ask~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <def_message-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <def_message-request>))
  "Converts a ROS message object to a list"
  (cl:list 'def_message-request
    (cl:cons ':ask (ask msg))
))
;//! \htmlinclude def_message-response.msg.html

(cl:defclass <def_message-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:integer
    :initform 0))
)

(cl:defclass def_message-response (<def_message-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <def_message-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'def_message-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name judge-srv:<def_message-response> is deprecated: use judge-srv:def_message-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <def_message-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader judge-srv:result-val is deprecated.  Use judge-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <def_message-response>) ostream)
  "Serializes a message object of type '<def_message-response>"
  (cl:let* ((signed (cl:slot-value msg 'result)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <def_message-response>) istream)
  "Deserializes a message object of type '<def_message-response>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<def_message-response>)))
  "Returns string type for a service object of type '<def_message-response>"
  "judge/def_messageResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'def_message-response)))
  "Returns string type for a service object of type 'def_message-response"
  "judge/def_messageResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<def_message-response>)))
  "Returns md5sum for a message object of type '<def_message-response>"
  "42c1fb09fc6033803973422ff2802e4e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'def_message-response)))
  "Returns md5sum for a message object of type 'def_message-response"
  "42c1fb09fc6033803973422ff2802e4e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<def_message-response>)))
  "Returns full string definition for message of type '<def_message-response>"
  (cl:format cl:nil "int64 result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'def_message-response)))
  "Returns full string definition for message of type 'def_message-response"
  (cl:format cl:nil "int64 result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <def_message-response>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <def_message-response>))
  "Converts a ROS message object to a list"
  (cl:list 'def_message-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'def_message)))
  'def_message-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'def_message)))
  'def_message-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'def_message)))
  "Returns string type for a service object of type '<def_message>"
  "judge/def_message")