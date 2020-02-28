// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hh"

// User implementation prologue.

#line 51 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 26 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:413

    #include "driver.hh"
    #include "location.hh"

//    #include "expressions/NumberExpression.h"
//    #include "expressions/AddExpression.h"
//    #include "expressions/MulExpression.h"
//    #include "expressions/DivExpression.h"
//    #include "expressions/SubstractExpression.h"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }

#line 68 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 154 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:479

  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 48: // "number"
        value.move< int > (that.value);
        break;

      case 47: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 48: // "number"
        value.copy< int > (that.value);
        break;

      case 47: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 48: // "number"
        yylhs.value.build< int > ();
        break;

      case 47: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 125 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 516 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 128 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 522 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 129 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 528 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 132 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 534 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 135 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 540 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 136 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 546 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 139 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 552 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 140 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 558 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 143 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 564 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 144 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 570 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 147 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 576 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 148 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 582 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 151 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 588 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 154 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 594 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 155 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 600 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 158 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 606 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 159 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 612 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 162 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 618 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 163 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 624 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 164 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 630 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 165 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 636 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 168 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 642 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 170 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 648 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 173 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 654 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 174 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 660 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 177 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 666 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 178 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 672 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 179 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 678 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 180 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 684 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 181 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 690 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 182 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 696 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 183 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 702 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 184 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 708 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 185 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 714 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 186 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 720 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 189 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 726 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 192 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 732 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 193 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 738 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 196 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 744 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 197 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 750 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 200 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 756 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 203 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 762 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 204 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 768 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 205 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 774 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 206 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 780 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 207 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 786 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 208 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 792 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 209 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 798 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 210 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 804 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 211 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 810 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 212 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 816 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 213 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 822 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 214 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 828 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 215 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 834 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 216 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 840 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 217 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:859
    {}
#line 846 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
    break;


#line 850 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -53;

  const signed char parser::yytable_ninf_ = -25;

  const short int
  parser::yypact_[] =
  {
      11,   -35,    27,   -53,    37,   -53,    47,    56,    23,   -53,
      68,    -1,    66,    29,   -53,    75,    62,     7,    61,   -53,
      22,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   -53,    45,
      76,   -53,   -53,    80,    42,    59,    82,    84,    91,   -53,
      90,   -53,   -53,   -53,     9,    85,    97,   -23,    79,    99,
     107,   111,   112,   170,    22,   -53,   -53,   118,   170,   170,
     -25,   -53,   -53,   -53,   -53,   117,   119,   306,   -53,   134,
      22,   -53,   170,   170,   170,   170,   -53,   -53,   254,   131,
     138,   106,   -53,   178,    35,   -53,   170,   170,   -14,   170,
     170,   170,   170,   170,   128,   -53,   122,   199,   206,   227,
     234,   -53,   170,   141,   -53,   -53,   260,   280,   -53,   157,
      35,    35,    67,    67,    67,   -53,   149,   -53,   -53,   168,
     168,   165,   286,   -53,   -53,   -53,    39,   -53,   172,   -53,
     -53,   -53,   -53,    10,   306,   168,   -53,   170,   -53,   306
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     4,     0,     1,     2,     0,     0,     3,
       0,     0,     0,     0,     9,     0,     0,     0,     0,     9,
       0,    21,    19,    20,     6,    24,     8,    11,    10,     0,
      17,    18,    22,     0,     0,     0,     0,     0,     0,     7,
       0,    14,    23,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    56,    26,     0,     0,     0,
      43,    44,    37,    25,    28,    57,     0,    42,    26,     0,
       0,    16,     0,     0,     0,     0,    43,    57,     0,     0,
      22,     0,     5,     0,    45,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,    34,     0,     0,    36,    51,     0,     0,    53,     0,
      46,    47,    48,    49,    50,    12,     0,    15,    27,     0,
       0,     0,     0,    55,    33,    52,     0,    13,    29,    31,
      32,    54,    39,     0,    41,     0,    38,     0,    30,    40
  };

  const short int
  parser::yypgoto_[] =
  {
     -53,   -53,   -53,   -53,   -53,   176,   -53,   -53,    28,   -53,
     -15,   144,   -53,   145,   -48,   -52,   -53,   -45,   -53,   -53,
     -49
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,     6,     3,     9,    17,    26,    27,    62,    47,
      29,    30,    31,    32,    45,    63,    64,    77,   133,    66,
      67
  };

  const short int
  parser::yytable_[] =
  {
      65,   -24,    69,   108,    78,    35,    70,    13,    81,    83,
      84,    20,     4,    21,     1,    21,    22,    23,    22,    23,
      94,    14,   -24,    97,    98,    99,   100,     5,    21,    48,
      24,    22,    23,   109,    46,   136,    65,   106,   107,   137,
     110,   111,   112,   113,   114,    28,    20,   116,    21,    65,
       8,    22,    23,   122,    25,    96,    25,    54,    55,     7,
      10,    87,    28,    58,   132,    39,    88,   128,   129,    25,
      11,    65,    15,    12,    65,    65,    16,   134,    91,    92,
      93,    59,    18,   138,    19,    33,    76,    61,   139,    25,
      65,    21,    36,    87,    22,    23,    49,    50,    88,    51,
      52,    53,    37,    54,    55,    38,    40,    56,    57,    58,
      41,    42,    21,    43,    44,    22,    23,    49,    50,    68,
      51,    52,    53,    72,    54,    55,    71,    59,    56,   104,
      58,    73,    60,    61,    21,    74,    75,    22,    23,    49,
      50,    82,    51,    52,    53,    85,    54,    55,    59,    86,
      56,   115,    58,    60,    61,    21,    95,   102,    22,    23,
      49,    50,   103,    51,    52,    53,   123,    54,    55,   117,
      59,    56,   127,    58,    21,    60,    61,    22,    23,    49,
      50,   126,    51,    52,    53,   135,    54,    55,    54,    55,
      56,    59,    58,   130,    58,    34,    60,    61,    79,    80,
       0,     0,     0,   105,    87,     0,     0,     0,     0,    88,
      59,     0,    59,     0,     0,    60,    61,    76,    61,    89,
      90,    91,    92,    93,   118,    87,     0,     0,     0,     0,
      88,   119,    87,     0,     0,     0,     0,    88,     0,     0,
      89,    90,    91,    92,    93,     0,     0,    89,    90,    91,
      92,    93,   120,    87,     0,     0,     0,     0,    88,   121,
      87,     0,     0,     0,     0,    88,     0,     0,    89,    90,
      91,    92,    93,     0,     0,    89,    90,    91,    92,    93,
      87,     0,   101,     0,     0,    88,    87,     0,   124,     0,
       0,    88,     0,     0,     0,    89,    90,    91,    92,    93,
       0,    89,    90,    91,    92,    93,    87,   125,     0,     0,
       0,    88,    87,   131,     0,     0,     0,    88,     0,     0,
       0,    89,    90,    91,    92,    93,     0,    89,    90,    91,
      92,    93,    87,     0,     0,     0,     0,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    89,    90,    91,
      92,    93
  };

  const short int
  parser::yycheck_[] =
  {
      45,    26,    25,    17,    53,    20,    29,     8,    56,    58,
      59,     4,    47,     6,     3,     6,     9,    10,     9,    10,
      68,    22,    47,    72,    73,    74,    75,     0,     6,    44,
      23,     9,    10,    47,    25,    25,    81,    86,    87,    29,
      89,    90,    91,    92,    93,    17,     4,    95,     6,    94,
       3,     9,    10,   102,    47,    70,    47,    18,    19,    22,
       4,    26,    34,    24,    25,    23,    31,   119,   120,    47,
      47,   116,     6,     5,   119,   120,    47,   126,    43,    44,
      45,    42,     7,   135,    22,    24,    47,    48,   137,    47,
     135,     6,    47,    26,     9,    10,    11,    12,    31,    14,
      15,    16,    26,    18,    19,    25,    47,    22,    23,    24,
      28,    27,     6,    22,    24,     9,    10,    11,    12,    22,
      14,    15,    16,    24,    18,    19,    47,    42,    22,    23,
      24,    24,    47,    48,     6,    24,    24,     9,    10,    11,
      12,    23,    14,    15,    16,    28,    18,    19,    42,    30,
      22,    23,    24,    47,    48,     6,    22,    26,     9,    10,
      11,    12,    24,    14,    15,    16,    25,    18,    19,    47,
      42,    22,    23,    24,     6,    47,    48,     9,    10,    11,
      12,    24,    14,    15,    16,    13,    18,    19,    18,    19,
      22,    42,    24,    28,    24,    19,    47,    48,    54,    54,
      -1,    -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    31,
      42,    -1,    42,    -1,    -1,    47,    48,    47,    48,    41,
      42,    43,    44,    45,    25,    26,    -1,    -1,    -1,    -1,
      31,    25,    26,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      41,    42,    43,    44,    45,    -1,    -1,    41,    42,    43,
      44,    45,    25,    26,    -1,    -1,    -1,    -1,    31,    25,
      26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    41,    42,
      43,    44,    45,    -1,    -1,    41,    42,    43,    44,    45,
      26,    -1,    28,    -1,    -1,    31,    26,    -1,    28,    -1,
      -1,    31,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      -1,    41,    42,    43,    44,    45,    26,    27,    -1,    -1,
      -1,    31,    26,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    -1,    41,    42,    43,
      44,    45,    26,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    45
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     3,    50,    52,    47,     0,    51,    22,     3,    53,
       4,    47,     5,     8,    22,     6,    47,    54,     7,    22,
       4,     6,     9,    10,    23,    47,    55,    56,    57,    59,
      60,    61,    62,    24,    54,    59,    47,    26,    25,    23,
      47,    28,    27,    22,    24,    63,    25,    58,    59,    11,
      12,    14,    15,    16,    18,    19,    22,    23,    24,    42,
      47,    48,    57,    64,    65,    66,    68,    69,    22,    25,
      29,    47,    24,    24,    24,    24,    47,    66,    69,    60,
      62,    63,    23,    69,    69,    28,    30,    26,    31,    41,
      42,    43,    44,    45,    63,    22,    59,    69,    69,    69,
      69,    28,    26,    24,    23,    25,    69,    69,    17,    47,
      69,    69,    69,    69,    69,    23,    63,    47,    25,    25,
      25,    25,    69,    25,    28,    27,    24,    23,    64,    64,
      28,    27,    25,    67,    69,    13,    25,    29,    64,    69
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    49,    50,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    61,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    66,    66,
      67,    67,    68,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,    13,     5,     7,     2,     0,
       1,     1,     8,     9,     3,     4,     2,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     0,     4,     1,     5,
       7,     5,     5,     4,     3,     2,     3,     1,     6,     5,
       3,     1,     1,     1,     1,     2,     3,     3,     3,     3,
       3,     3,     4,     3,     5,     4,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"class\"", "\"public\"",
  "\"static\"", "\"void\"", "\"main\"", "\"extends\"", "\"int\"",
  "\"boolean\"", "\"assert\"", "\"if\"", "\"else\"", "\"while\"",
  "\"System.out.println\"", "\"return\"", "\"length\"", "\"new\"",
  "\"this\"", "\"true\"", "\"false\"", "\"{\"", "\"}\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\";\"", "\",\"", "\"=\"", "\".\"", "\"!\"", "\"&&\"",
  "\"||\"", "\"<\"", "\">\"", "\"<=\"", "\">=\"", "\"==\"", "\"!=\"",
  "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "UMINUS", "\"identifier\"",
  "\"number\"", "$accept", "program", "class_declarations", "main_class",
  "class_declaration", "declarations", "declaration", "method_declaration",
  "variable_declaration", "formals", "type", "simple_type", "array_type",
  "type_identifier", "statements", "statement",
  "local_variable_declaration", "method_invocation", "method_expression",
  "lvalue", "expression", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,   125,   125,   128,   129,   132,   135,   136,   139,   140,
     143,   144,   147,   148,   151,   154,   155,   158,   159,   162,
     163,   164,   165,   168,   170,   173,   174,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   189,   192,   193,
     196,   197,   200,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG



} // yy
#line 1264 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.cpp" // lalr1.cc:1167
#line 233 "/home/wasd/github/Mini-Java-Compiler/interpreter/parser.y" // lalr1.cc:1168

