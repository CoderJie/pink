// Copyright (c) 2015-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.
#ifndef PINK_CONN_H_
#define PINK_CONN_H_

#include <sys/time.h>
#include <string>
#include "pink_define.h"

namespace pink {

class PinkConn
{
public:
  PinkConn(const int fd, const std::string &ip_port);
  virtual ~PinkConn();
  
  /*
   * Set the fd to nonblock && set the flag_ the the fd flag
   */
  bool SetNonblock();

  int flags() { 
    return flags_; 
  };

  virtual ReadStatus GetRequest() = 0;
  virtual WriteStatus SendReply() = 0;

  void set_fd(const int fd) { 
    fd_ = fd; 
  }
  int fd() const {
    return fd_;
  }

  std::string ip_port() const {
    return ip_port_;
  }

  void set_is_reply(const bool is_reply) {
    is_reply_ = is_reply;
  }

  bool is_reply() const {
    return is_reply_;
  }

  void set_last_interaction(const struct timeval &now) {
    last_interaction_ = now;
  }

  struct timeval last_interaction() const {
    return last_interaction_;
  };

private:
  
  int fd_;
  std::string ip_port_;
  bool is_reply_;
  struct timeval last_interaction_;
  int flags_;


  /*
   * No allowed copy and copy assign operator
   */
  PinkConn(const PinkConn&);
  void operator=(const PinkConn&);
};
}

#endif
