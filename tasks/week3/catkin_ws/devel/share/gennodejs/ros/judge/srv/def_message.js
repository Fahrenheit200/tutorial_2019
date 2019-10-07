// Auto-generated. Do not edit!

// (in-package judge.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class def_messageRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ask = null;
    }
    else {
      if (initObj.hasOwnProperty('ask')) {
        this.ask = initObj.ask
      }
      else {
        this.ask = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type def_messageRequest
    // Serialize message field [ask]
    bufferOffset = _serializer.float64(obj.ask, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type def_messageRequest
    let len;
    let data = new def_messageRequest(null);
    // Deserialize message field [ask]
    data.ask = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'judge/def_messageRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ddbe15febb103006edb58c3b0b204bed';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 ask
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new def_messageRequest(null);
    if (msg.ask !== undefined) {
      resolved.ask = msg.ask;
    }
    else {
      resolved.ask = 0.0
    }

    return resolved;
    }
};

class def_messageResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.result = null;
    }
    else {
      if (initObj.hasOwnProperty('result')) {
        this.result = initObj.result
      }
      else {
        this.result = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type def_messageResponse
    // Serialize message field [result]
    bufferOffset = _serializer.int64(obj.result, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type def_messageResponse
    let len;
    let data = new def_messageResponse(null);
    // Deserialize message field [result]
    data.result = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'judge/def_messageResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9b05623554ab950ed237d43d45f0b4dd';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 result
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new def_messageResponse(null);
    if (msg.result !== undefined) {
      resolved.result = msg.result;
    }
    else {
      resolved.result = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: def_messageRequest,
  Response: def_messageResponse,
  md5sum() { return '42c1fb09fc6033803973422ff2802e4e'; },
  datatype() { return 'judge/def_message'; }
};
