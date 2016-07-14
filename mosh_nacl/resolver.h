// resolver.h - Interface for DNS lookups.

// Copyright 2016 Richard Woodbury
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RESOLVER_H
#define RESOLVER_H

#include <functional>
#include <string>
#include <vector>

class Resolver {
 public:
  Resolver() = default;
  Resolver(const Resolver&) = delete;
  Resolver& operator=(const Resolver&) = delete;
  Resolver(Resolver&&) = default;
  Resolver& operator=(Resolver&&) = default;
  virtual ~Resolver() = default;

  // Data type.
  enum class Type {
    A,
    AAAA,
    SSHFP,
  };

  // Error codes.
  enum class Error {
    OK,
    NOT_RESOLVED,
    TYPE_NOT_SUPPORTED,
    UNKNOWN,
  };

  // Resolve |domain_name| to the given |type|. Returns immediately; calls
  // |callback| with result. If callback's |error| != Error::OK, |results| is
  // empty.
  //
  // |domain_name| is taken by value as a stable copy is needed. Callers can
  // std::move() it if desired for efficiency.
  virtual void Resolve(
      std::string domain_name,
      Type type,
      std::function<void(Error error, std::vector<std::string> results)> callback) = 0;
};

#endif // RESOLVER_H