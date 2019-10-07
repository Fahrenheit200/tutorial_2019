
(cl:in-package :asdf)

(defsystem "judge-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "def_message" :depends-on ("_package_def_message"))
    (:file "_package_def_message" :depends-on ("_package"))
  ))