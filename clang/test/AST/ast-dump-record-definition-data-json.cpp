// RUN: %clang_cc1 -triple x86_64-unknown-unknown -std=c++17 -ast-dump=json %s | FileCheck %s

void f() {
  auto IsNotGenericLambda = [](){};
  auto IsGenericLambda = [](auto){};
}

struct CanPassInRegisters {
  CanPassInRegisters(const CanPassInRegisters&) = default;
};

struct CantPassInRegisters {
  CantPassInRegisters(const CantPassInRegisters&) = delete;
};

struct IsEmpty {
};

struct IsNotEmpty {
  int a;
};

struct IsAggregate {
  int a;
};

struct IsNotAggregate {
private:
  int a;
};

struct IsStandardLayout {
  void f();
};

struct IsNotStandardLayout {
  virtual void f();
};

struct IsTriviallyCopyable {
};

struct IsNotTriviallyCopyable {
  IsNotTriviallyCopyable(const IsNotTriviallyCopyable&) {}
};

struct IsPOD {
  int a;
};

struct IsNotPOD {
  int &a;
};

struct IsTrivial {
  IsTrivial() = default;
};

struct IsNotTrivial {
  IsNotTrivial() {}
};

struct IsPolymorphic {
  virtual void f();
};

struct IsNotPolymorphic {
  void f();
};

struct IsAbstract {
  virtual void f() = 0;
};

struct IsNotAbstract {
  virtual void f();
};

struct IsLiteral {
  ~IsLiteral() = default;
};

struct IsNotLiteral {
  ~IsNotLiteral() {}
};

struct HasUserDeclaredConstructor {
  HasUserDeclaredConstructor() {}
};

struct HasNoUserDeclaredConstructor {
};

struct HasConstexprNonCopyMoveConstructor {
  constexpr HasConstexprNonCopyMoveConstructor() {}
};

struct HasNoConstexprNonCopyMoveConstructor {
  HasNoConstexprNonCopyMoveConstructor() {}
};

struct HasMutableFields {
  mutable int i;
};

struct HasNoMutableFields {
  int i;
};

struct HasVariantMembers {
  union {
    int i;
  };
};

struct HasNoVariantMembers {
};

struct AllowsConstDefaultInit {
  int i = 12;
};

struct DoesNotAllowConstDefaultInit {
  int i;
};


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 29,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 4
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 29,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 4
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 29,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 4
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "isImplicit": true,
// CHECK-NEXT:  "tagUsed": "class",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLambda": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 29,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 4
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 32,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 34,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "operator()",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void () const"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 33,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 4
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 34,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 4
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConversionDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 29,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 4
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 29,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 34,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator void (*)()",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void (*() const noexcept)()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 29,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 4
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 29,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 34,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "__invoke",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "storageClass": "static",
// CHECK-NEXT:    "inline": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 29,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 4
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 29,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 29,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 4
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "~",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void () noexcept"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 26,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 5
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 26,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 5
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 26,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 5
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "isImplicit": true,
// CHECK-NEXT:  "tagUsed": "class",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isGenericLambda": true,
// CHECK-NEXT:   "isLambda": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FunctionTemplateDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 26,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 5
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {},
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 35,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 5
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "operator()",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "TemplateTypeParmDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 29,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 5
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 29,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 29,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "isImplicit": true,
// CHECK-NEXT:      "tagUsed": "class",
// CHECK-NEXT:      "depth": 0,
// CHECK-NEXT:      "index": 0
// CHECK-NEXT:     },
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CXXMethodDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 26,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 5
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 33,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 35,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "name": "operator()",
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "auto (auto) const"
// CHECK-NEXT:      },
// CHECK-NEXT:      "inline": true,
// CHECK-NEXT:      "constexpr": true,
// CHECK-NEXT:      "inner": [
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "ParmVarDecl",
// CHECK-NEXT:        "loc": {
// CHECK-NEXT:         "col": 33,
// CHECK-NEXT:         "file": "{{.*}}",
// CHECK-NEXT:         "line": 5
// CHECK-NEXT:        },
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "col": 29,
// CHECK-NEXT:          "file": "{{.*}}",
// CHECK-NEXT:          "line": 5
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "col": 29,
// CHECK-NEXT:          "file": "{{.*}}",
// CHECK-NEXT:          "line": 5
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "type": {
// CHECK-NEXT:         "qualType": "auto"
// CHECK-NEXT:        }
// CHECK-NEXT:       },
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "CompoundStmt",
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "col": 34,
// CHECK-NEXT:          "file": "{{.*}}",
// CHECK-NEXT:          "line": 5
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "col": 35,
// CHECK-NEXT:          "file": "{{.*}}",
// CHECK-NEXT:          "line": 5
// CHECK-NEXT:         }
// CHECK-NEXT:        }
// CHECK-NEXT:       }
// CHECK-NEXT:      ]
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FunctionTemplateDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 26,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 5
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {},
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 35,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 5
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator auto (*)(type-parameter-0-0)",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "TemplateTypeParmDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 29,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 5
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 29,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 29,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "isImplicit": true,
// CHECK-NEXT:      "tagUsed": "class",
// CHECK-NEXT:      "depth": 0,
// CHECK-NEXT:      "index": 0
// CHECK-NEXT:     },
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CXXConversionDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 26,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 5
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 26,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 35,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "isImplicit": true,
// CHECK-NEXT:      "name": "operator auto (*)(type-parameter-0-0)",
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "auto (*() const noexcept)(auto)"
// CHECK-NEXT:      },
// CHECK-NEXT:      "inline": true,
// CHECK-NEXT:      "constexpr": true
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FunctionTemplateDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 26,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 5
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {},
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 35,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 5
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "__invoke",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "TemplateTypeParmDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 29,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 5
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 29,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 29,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "isImplicit": true,
// CHECK-NEXT:      "tagUsed": "class",
// CHECK-NEXT:      "depth": 0,
// CHECK-NEXT:      "index": 0
// CHECK-NEXT:     },
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CXXMethodDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 26,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 5
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 26,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 35,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 5
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "isImplicit": true,
// CHECK-NEXT:      "name": "__invoke",
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "auto (auto)"
// CHECK-NEXT:      },
// CHECK-NEXT:      "storageClass": "static",
// CHECK-NEXT:      "inline": true,
// CHECK-NEXT:      "inner": [
// CHECK-NEXT:       {
// CHECK-NEXT:        "id": "0x{{.*}}",
// CHECK-NEXT:        "kind": "ParmVarDecl",
// CHECK-NEXT:        "loc": {
// CHECK-NEXT:         "col": 33,
// CHECK-NEXT:         "file": "{{.*}}",
// CHECK-NEXT:         "line": 5
// CHECK-NEXT:        },
// CHECK-NEXT:        "range": {
// CHECK-NEXT:         "begin": {
// CHECK-NEXT:          "col": 29,
// CHECK-NEXT:          "file": "{{.*}}",
// CHECK-NEXT:          "line": 5
// CHECK-NEXT:         },
// CHECK-NEXT:         "end": {
// CHECK-NEXT:          "col": 29,
// CHECK-NEXT:          "file": "{{.*}}",
// CHECK-NEXT:          "line": 5
// CHECK-NEXT:         }
// CHECK-NEXT:        },
// CHECK-NEXT:        "type": {
// CHECK-NEXT:         "qualType": "auto"
// CHECK-NEXT:        }
// CHECK-NEXT:       }
// CHECK-NEXT:      ]
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 26,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 5
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 26,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 5
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 26,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 5
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "~",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void () noexcept"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 8
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 8
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 10
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "CanPassInRegisters",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "trivial": true,
// CHECK-NEXT:    "userDeclared": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {}
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 8
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 8
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 8
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "CanPassInRegisters",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 9
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 9
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 57,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 9
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "CanPassInRegisters",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void (const CanPassInRegisters &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 47,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 9
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 22,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 9
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 46,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 9
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const CanPassInRegisters &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 12
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 12
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 14
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "CantPassInRegisters",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "trivial": true,
// CHECK-NEXT:    "userDeclared": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {}
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 12
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 12
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 12
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "CantPassInRegisters",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 13
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 13
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 58,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 13
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "CantPassInRegisters",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void (const CantPassInRegisters &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "explicitlyDeleted": true,
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 49,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 13
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 23,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 13
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 48,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 13
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const CantPassInRegisters &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 16
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 16
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 17
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsEmpty",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 16
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 16
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 16
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsEmpty",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 19
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 19
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 21
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotEmpty",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 19
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 19
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 19
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsNotEmpty",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 20
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 20
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 7,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 20
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "a",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 23
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 23
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 25
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsAggregate",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 23
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 23
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 23
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsAggregate",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 24
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 24
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 7,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 24
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "a",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 27
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 27
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 30
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotAggregate",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 27
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 27
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 27
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsNotAggregate",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "AccessSpecDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 1,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 28
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 28
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 28
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "access": "private"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 29
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 29
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 7,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 29
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "a",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 32
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 32
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 34
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsStandardLayout",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 32
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 32
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 32
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsStandardLayout",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 33
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 33
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 10,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 33
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "f",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 36
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 36
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 38
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotStandardLayout",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPolymorphic": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 36
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsNotStandardLayout",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 16,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 37
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 37
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 18,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 37
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "f",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "virtual": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 36
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsNotStandardLayout &(const IsNotStandardLayout &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 36
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 36
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 36
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const IsNotStandardLayout &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 36
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsNotStandardLayout &(IsNotStandardLayout &&)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 36
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 36
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 36
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "IsNotStandardLayout &&"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 36
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 36
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "~IsNotStandardLayout",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 40
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 40
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 41
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsTriviallyCopyable",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 40
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 40
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 40
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsTriviallyCopyable",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 43
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 43
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 45
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotTriviallyCopyable",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "userDeclared": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {}
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 43
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 43
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 43
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "IsNotTriviallyCopyable",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 44
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 44
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 58,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 44
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "IsNotTriviallyCopyable",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void (const IsNotTriviallyCopyable &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 55,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 44
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 26,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 44
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 54,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 44
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const IsNotTriviallyCopyable &"
// CHECK-NEXT:      }
// CHECK-NEXT:     },
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 57,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 44
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 58,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 44
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 47
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 47
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 49
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsPOD",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 47
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 47
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 47
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsPOD",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 48
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 48
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 7,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 48
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "a",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 51
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 51
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 53
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotPOD",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 51
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 51
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 51
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsNotPOD",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 52
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 52
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 52
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "a",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int &"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 55
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 55
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 57
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsTrivial",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 55
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 55
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 55
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "IsTrivial",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 56
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 56
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 23,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 56
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "IsTrivial",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 59
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 59
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 61
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotTrivial",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "userProvided": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 59
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 59
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 59
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "IsNotTrivial",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 60
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 60
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 19,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 60
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "IsNotTrivial",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 18,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 60
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 19,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 60
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 63
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 63
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 65
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsPolymorphic",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPolymorphic": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 63
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsPolymorphic",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 16,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 64
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 64
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 18,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 64
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "f",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "virtual": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 63
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsPolymorphic &(const IsPolymorphic &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 63
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 63
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 63
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const IsPolymorphic &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 63
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsPolymorphic &(IsPolymorphic &&)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 63
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 63
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 63
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "IsPolymorphic &&"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 63
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 63
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "~IsPolymorphic",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 67
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 67
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 69
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotPolymorphic",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 67
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 67
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 67
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsNotPolymorphic",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 68
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 68
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 10,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 68
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "f",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 71
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 71
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 73
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsAbstract",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAbstract": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPolymorphic": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 71
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsAbstract",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 16,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 72
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 72
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 22,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 72
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "f",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "virtual": true,
// CHECK-NEXT:    "pure": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 71
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsAbstract &(const IsAbstract &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 71
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 71
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 71
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const IsAbstract &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 71
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsAbstract &(IsAbstract &&)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 71
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 71
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 71
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "IsAbstract &&"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 71
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 71
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "~IsAbstract",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 75
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 75
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 77
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotAbstract",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPolymorphic": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "simple": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 75
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "IsNotAbstract",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 16,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 76
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 76
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 18,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 76
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "f",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "virtual": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 75
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsNotAbstract &(const IsNotAbstract &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 75
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 75
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 75
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const IsNotAbstract &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 75
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "IsNotAbstract &(IsNotAbstract &&)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 75
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 75
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 75
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "IsNotAbstract &&"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 75
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 75
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "~IsNotAbstract",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 79
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 79
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 81
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsLiteral",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "trivial": true,
// CHECK-NEXT:    "userDeclared": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {}
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 79
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 79
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 79
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "IsLiteral",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 80
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 80
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 24,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 80
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "~IsLiteral",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "explicitlyDefaulted": "default"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 83
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 83
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 85
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "IsNotLiteral",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "userDeclared": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "moveAssign": {},
// CHECK-NEXT:   "moveCtor": {}
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 83
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 83
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 83
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "IsNotLiteral",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXDestructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 84
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 84
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 20,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 84
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "~IsNotLiteral",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void () noexcept"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 19,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 84
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 20,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 84
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 87
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 87
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 89
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasUserDeclaredConstructor",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "userProvided": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 87
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 87
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 87
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "HasUserDeclaredConstructor",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 88
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 88
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 33,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 88
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "HasUserDeclaredConstructor",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 32,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 88
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 33,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 88
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 91
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 91
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 92
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasNoUserDeclaredConstructor",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 91
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 91
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 91
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "HasNoUserDeclaredConstructor",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 94
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 94
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 96
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasConstexprNonCopyMoveConstructor",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "userProvided": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 94
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 94
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 94
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "HasConstexprNonCopyMoveConstructor",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 13,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 95
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 95
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 51,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 95
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "HasConstexprNonCopyMoveConstructor",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 50,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 95
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 51,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 95
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 98
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 98
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 100
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasNoConstexprNonCopyMoveConstructor",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "nonTrivial": true,
// CHECK-NEXT:    "userProvided": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasUserDeclaredConstructor": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 98
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 98
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 98
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "isReferenced": true,
// CHECK-NEXT:    "name": "HasNoConstexprNonCopyMoveConstructor",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 99
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 99
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 43,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 99
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "HasNoConstexprNonCopyMoveConstructor",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void ()"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "CompoundStmt",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 42,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 99
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 43,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 99
// CHECK-NEXT:       }
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 102
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 102
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 104
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasMutableFields",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsOverloadResolution": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsOverloadResolution": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasMutableFields": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 102
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 102
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 102
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "HasMutableFields",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 15,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 103
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 103
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 15,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 103
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "i",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    },
// CHECK-NEXT:    "mutable": true
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXConstructorDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 102
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 102
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 102
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "HasMutableFields",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "void (const HasMutableFields &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 102
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 102
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 102
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const HasMutableFields &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXMethodDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 102
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 102
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 102
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "operator=",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "HasMutableFields &(const HasMutableFields &)"
// CHECK-NEXT:    },
// CHECK-NEXT:    "inline": true,
// CHECK-NEXT:    "constexpr": true,
// CHECK-NEXT:    "explicitlyDefaulted": "default",
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "ParmVarDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 8,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 102
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 102
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 8,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 102
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "const HasMutableFields &"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 106
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 106
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 108
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasNoMutableFields",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 106
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 106
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 106
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "HasNoMutableFields",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 107
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 107
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 7,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 107
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "i",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 110
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 110
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 114
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasVariantMembers",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasVariantMembers": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 110
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 110
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 110
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "HasVariantMembers",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 111
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 111
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 113
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "tagUsed": "union",
// CHECK-NEXT:    "completeDefinition": true,
// CHECK-NEXT:    "definitionData": {
// CHECK-NEXT:     "canPassInRegisters": true,
// CHECK-NEXT:     "copyAssign": {
// CHECK-NEXT:      "hasConstParam": true,
// CHECK-NEXT:      "implicitHasConstParam": true,
// CHECK-NEXT:      "needsImplicit": true,
// CHECK-NEXT:      "trivial": true
// CHECK-NEXT:     },
// CHECK-NEXT:     "copyCtor": {
// CHECK-NEXT:      "hasConstParam": true,
// CHECK-NEXT:      "implicitHasConstParam": true,
// CHECK-NEXT:      "needsImplicit": true,
// CHECK-NEXT:      "simple": true,
// CHECK-NEXT:      "trivial": true
// CHECK-NEXT:     },
// CHECK-NEXT:     "defaultCtor": {
// CHECK-NEXT:      "exists": true,
// CHECK-NEXT:      "needsImplicit": true,
// CHECK-NEXT:      "trivial": true
// CHECK-NEXT:     },
// CHECK-NEXT:     "dtor": {
// CHECK-NEXT:      "irrelevant": true,
// CHECK-NEXT:      "needsImplicit": true,
// CHECK-NEXT:      "simple": true,
// CHECK-NEXT:      "trivial": true
// CHECK-NEXT:     },
// CHECK-NEXT:     "hasVariantMembers": true,
// CHECK-NEXT:     "isAggregate": true,
// CHECK-NEXT:     "isLiteral": true,
// CHECK-NEXT:     "isPOD": true,
// CHECK-NEXT:     "isStandardLayout": true,
// CHECK-NEXT:     "isTrivial": true,
// CHECK-NEXT:     "isTriviallyCopyable": true,
// CHECK-NEXT:     "moveAssign": {
// CHECK-NEXT:      "exists": true,
// CHECK-NEXT:      "needsImplicit": true,
// CHECK-NEXT:      "simple": true,
// CHECK-NEXT:      "trivial": true
// CHECK-NEXT:     },
// CHECK-NEXT:     "moveCtor": {
// CHECK-NEXT:      "exists": true,
// CHECK-NEXT:      "needsImplicit": true,
// CHECK-NEXT:      "simple": true,
// CHECK-NEXT:      "trivial": true
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "FieldDecl",
// CHECK-NEXT:      "loc": {
// CHECK-NEXT:       "col": 9,
// CHECK-NEXT:       "file": "{{.*}}",
// CHECK-NEXT:       "line": 112
// CHECK-NEXT:      },
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 5,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 112
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 9,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 112
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "name": "i",
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "int"
// CHECK-NEXT:      }
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 3,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 111
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 111
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 111
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "HasVariantMembers::(anonymous union at {{.*}}:111:3)"
// CHECK-NEXT:    }
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "IndirectFieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 9,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 112
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 9,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 112
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 9,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 112
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "i"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 116
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 116
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 117
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "HasNoVariantMembers",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isEmpty": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 116
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 116
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 116
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "HasNoVariantMembers",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 119
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 119
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 121
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "AllowsConstDefaultInit",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canConstDefaultInit": true,
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "defaultedIsConstexpr": true,
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "isConstexpr": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "nonTrivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "hasConstexprNonCopyMoveConstructor": true,
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 119
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 119
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 119
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "AllowsConstDefaultInit",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 120
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 120
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 11,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 120
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "i",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    },
// CHECK-NEXT:    "hasInClassInitializer": true,
// CHECK-NEXT:    "inner": [
// CHECK-NEXT:     {
// CHECK-NEXT:      "id": "0x{{.*}}",
// CHECK-NEXT:      "kind": "IntegerLiteral",
// CHECK-NEXT:      "range": {
// CHECK-NEXT:       "begin": {
// CHECK-NEXT:        "col": 11,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 120
// CHECK-NEXT:       },
// CHECK-NEXT:       "end": {
// CHECK-NEXT:        "col": 11,
// CHECK-NEXT:        "file": "{{.*}}",
// CHECK-NEXT:        "line": 120
// CHECK-NEXT:       }
// CHECK-NEXT:      },
// CHECK-NEXT:      "type": {
// CHECK-NEXT:       "qualType": "int"
// CHECK-NEXT:      },
// CHECK-NEXT:      "valueCategory": "rvalue",
// CHECK-NEXT:      "value": "12"
// CHECK-NEXT:     }
// CHECK-NEXT:    ]
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }


// CHECK:  "kind": "CXXRecordDecl",
// CHECK-NEXT:  "loc": {
// CHECK-NEXT:   "col": 8,
// CHECK-NEXT:   "file": "{{.*}}",
// CHECK-NEXT:   "line": 123
// CHECK-NEXT:  },
// CHECK-NEXT:  "range": {
// CHECK-NEXT:   "begin": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 123
// CHECK-NEXT:   },
// CHECK-NEXT:   "end": {
// CHECK-NEXT:    "col": 1,
// CHECK-NEXT:    "file": "{{.*}}",
// CHECK-NEXT:    "line": 125
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "name": "DoesNotAllowConstDefaultInit",
// CHECK-NEXT:  "tagUsed": "struct",
// CHECK-NEXT:  "completeDefinition": true,
// CHECK-NEXT:  "definitionData": {
// CHECK-NEXT:   "canPassInRegisters": true,
// CHECK-NEXT:   "copyAssign": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "copyCtor": {
// CHECK-NEXT:    "hasConstParam": true,
// CHECK-NEXT:    "implicitHasConstParam": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "defaultCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "dtor": {
// CHECK-NEXT:    "irrelevant": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "isAggregate": true,
// CHECK-NEXT:   "isLiteral": true,
// CHECK-NEXT:   "isPOD": true,
// CHECK-NEXT:   "isStandardLayout": true,
// CHECK-NEXT:   "isTrivial": true,
// CHECK-NEXT:   "isTriviallyCopyable": true,
// CHECK-NEXT:   "moveAssign": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   },
// CHECK-NEXT:   "moveCtor": {
// CHECK-NEXT:    "exists": true,
// CHECK-NEXT:    "needsImplicit": true,
// CHECK-NEXT:    "simple": true,
// CHECK-NEXT:    "trivial": true
// CHECK-NEXT:   }
// CHECK-NEXT:  },
// CHECK-NEXT:  "inner": [
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "CXXRecordDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 8,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 123
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 1,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 123
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 8,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 123
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "isImplicit": true,
// CHECK-NEXT:    "name": "DoesNotAllowConstDefaultInit",
// CHECK-NEXT:    "tagUsed": "struct"
// CHECK-NEXT:   },
// CHECK-NEXT:   {
// CHECK-NEXT:    "id": "0x{{.*}}",
// CHECK-NEXT:    "kind": "FieldDecl",
// CHECK-NEXT:    "loc": {
// CHECK-NEXT:     "col": 7,
// CHECK-NEXT:     "file": "{{.*}}",
// CHECK-NEXT:     "line": 124
// CHECK-NEXT:    },
// CHECK-NEXT:    "range": {
// CHECK-NEXT:     "begin": {
// CHECK-NEXT:      "col": 3,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 124
// CHECK-NEXT:     },
// CHECK-NEXT:     "end": {
// CHECK-NEXT:      "col": 7,
// CHECK-NEXT:      "file": "{{.*}}",
// CHECK-NEXT:      "line": 124
// CHECK-NEXT:     }
// CHECK-NEXT:    },
// CHECK-NEXT:    "name": "i",
// CHECK-NEXT:    "type": {
// CHECK-NEXT:     "qualType": "int"
// CHECK-NEXT:    }
// CHECK-NEXT:   }
// CHECK-NEXT:  ]
// CHECK-NEXT: }
