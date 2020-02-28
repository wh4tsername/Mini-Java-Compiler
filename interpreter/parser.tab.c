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

#line 37 "parser.tab.c" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.h"

// User implementation prologue.

#line 51 "parser.tab.c" // lalr1.cc:412
// Unqualified %code blocks.
#line 26 "parser.y" // lalr1.cc:413

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

#line 68 "parser.tab.c" // lalr1.cc:413


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
#line 154 "parser.tab.c" // lalr1.cc:479

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
#line 125 "parser.y" // lalr1.cc:859
    {}
#line 516 "parser.tab.c" // lalr1.cc:859
    break;

  case 3:
#line 128 "parser.y" // lalr1.cc:859
    {}
#line 522 "parser.tab.c" // lalr1.cc:859
    break;

  case 4:
#line 129 "parser.y" // lalr1.cc:859
    {}
#line 528 "parser.tab.c" // lalr1.cc:859
    break;

  case 5:
#line 132 "parser.y" // lalr1.cc:859
    {}
#line 534 "parser.tab.c" // lalr1.cc:859
    break;

  case 6:
#line 135 "parser.y" // lalr1.cc:859
    {}
#line 540 "parser.tab.c" // lalr1.cc:859
    break;

  case 7:
#line 136 "parser.y" // lalr1.cc:859
    {}
#line 546 "parser.tab.c" // lalr1.cc:859
    break;

  case 8:
#line 139 "parser.y" // lalr1.cc:859
    {}
#line 552 "parser.tab.c" // lalr1.cc:859
    break;

  case 9:
#line 140 "parser.y" // lalr1.cc:859
    {}
#line 558 "parser.tab.c" // lalr1.cc:859
    break;

  case 10:
#line 143 "parser.y" // lalr1.cc:859
    {}
#line 564 "parser.tab.c" // lalr1.cc:859
    break;

  case 11:
#line 144 "parser.y" // lalr1.cc:859
    {}
#line 570 "parser.tab.c" // lalr1.cc:859
    break;

  case 12:
#line 147 "parser.y" // lalr1.cc:859
    {}
#line 576 "parser.tab.c" // lalr1.cc:859
    break;

  case 13:
#line 148 "parser.y" // lalr1.cc:859
    {}
#line 582 "parser.tab.c" // lalr1.cc:859
    break;

  case 14:
#line 151 "parser.y" // lalr1.cc:859
    {}
#line 588 "parser.tab.c" // lalr1.cc:859
    break;

  case 15:
#line 154 "parser.y" // lalr1.cc:859
    {}
#line 594 "parser.tab.c" // lalr1.cc:859
    break;

  case 16:
#line 155 "parser.y" // lalr1.cc:859
    {}
#line 600 "parser.tab.c" // lalr1.cc:859
    break;

  case 17:
#line 158 "parser.y" // lalr1.cc:859
    {}
#line 606 "parser.tab.c" // lalr1.cc:859
    break;

  case 18:
#line 159 "parser.y" // lalr1.cc:859
    {}
#line 612 "parser.tab.c" // lalr1.cc:859
    break;

  case 19:
#line 162 "parser.y" // lalr1.cc:859
    {}
#line 618 "parser.tab.c" // lalr1.cc:859
    break;

  case 20:
#line 163 "parser.y" // lalr1.cc:859
    {}
#line 624 "parser.tab.c" // lalr1.cc:859
    break;

  case 21:
#line 164 "parser.y" // lalr1.cc:859
    {}
#line 630 "parser.tab.c" // lalr1.cc:859
    break;

  case 22:
#line 165 "parser.y" // lalr1.cc:859
    {}
#line 636 "parser.tab.c" // lalr1.cc:859
    break;

  case 23:
#line 168 "parser.y" // lalr1.cc:859
    {}
#line 642 "parser.tab.c" // lalr1.cc:859
    break;

  case 24:
#line 170 "parser.y" // lalr1.cc:859
    {}
#line 648 "parser.tab.c" // lalr1.cc:859
    break;

  case 25:
#line 173 "parser.y" // lalr1.cc:859
    {}
#line 654 "parser.tab.c" // lalr1.cc:859
    break;

  case 26:
#line 174 "parser.y" // lalr1.cc:859
    {}
#line 660 "parser.tab.c" // lalr1.cc:859
    break;

  case 27:
#line 177 "parser.y" // lalr1.cc:859
    {}
#line 666 "parser.tab.c" // lalr1.cc:859
    break;

  case 28:
#line 178 "parser.y" // lalr1.cc:859
    {}
#line 672 "parser.tab.c" // lalr1.cc:859
    break;

  case 29:
#line 179 "parser.y" // lalr1.cc:859
    {}
#line 678 "parser.tab.c" // lalr1.cc:859
    break;

  case 30:
#line 180 "parser.y" // lalr1.cc:859
    {}
#line 684 "parser.tab.c" // lalr1.cc:859
    break;

  case 31:
#line 181 "parser.y" // lalr1.cc:859
    {}
#line 690 "parser.tab.c" // lalr1.cc:859
    break;

  case 32:
#line 182 "parser.y" // lalr1.cc:859
    {}
#line 696 "parser.tab.c" // lalr1.cc:859
    break;

  case 33:
#line 183 "parser.y" // lalr1.cc:859
    {}
#line 702 "parser.tab.c" // lalr1.cc:859
    break;

  case 34:
#line 184 "parser.y" // lalr1.cc:859
    {}
#line 708 "parser.tab.c" // lalr1.cc:859
    break;

  case 35:
#line 185 "parser.y" // lalr1.cc:859
    {}
#line 714 "parser.tab.c" // lalr1.cc:859
    break;

  case 36:
#line 186 "parser.y" // lalr1.cc:859
    {}
#line 720 "parser.tab.c" // lalr1.cc:859
    break;

  case 37:
#line 187 "parser.y" // lalr1.cc:859
    {}
#line 726 "parser.tab.c" // lalr1.cc:859
    break;

  case 38:
#line 188 "parser.y" // lalr1.cc:859
    {}
#line 732 "parser.tab.c" // lalr1.cc:859
    break;

  case 39:
#line 189 "parser.y" // lalr1.cc:859
    {}
#line 738 "parser.tab.c" // lalr1.cc:859
    break;

  case 40:
#line 190 "parser.y" // lalr1.cc:859
    {}
#line 744 "parser.tab.c" // lalr1.cc:859
    break;

  case 41:
#line 191 "parser.y" // lalr1.cc:859
    {}
#line 750 "parser.tab.c" // lalr1.cc:859
    break;

  case 42:
#line 194 "parser.y" // lalr1.cc:859
    {}
#line 756 "parser.tab.c" // lalr1.cc:859
    break;

  case 43:
#line 197 "parser.y" // lalr1.cc:859
    {}
#line 762 "parser.tab.c" // lalr1.cc:859
    break;

  case 44:
#line 198 "parser.y" // lalr1.cc:859
    {}
#line 768 "parser.tab.c" // lalr1.cc:859
    break;

  case 45:
#line 201 "parser.y" // lalr1.cc:859
    {}
#line 774 "parser.tab.c" // lalr1.cc:859
    break;

  case 46:
#line 202 "parser.y" // lalr1.cc:859
    {}
#line 780 "parser.tab.c" // lalr1.cc:859
    break;

  case 47:
#line 205 "parser.y" // lalr1.cc:859
    {}
#line 786 "parser.tab.c" // lalr1.cc:859
    break;

  case 48:
#line 208 "parser.y" // lalr1.cc:859
    {}
#line 792 "parser.tab.c" // lalr1.cc:859
    break;

  case 49:
#line 209 "parser.y" // lalr1.cc:859
    {}
#line 798 "parser.tab.c" // lalr1.cc:859
    break;

  case 50:
#line 210 "parser.y" // lalr1.cc:859
    {}
#line 804 "parser.tab.c" // lalr1.cc:859
    break;

  case 51:
#line 211 "parser.y" // lalr1.cc:859
    {}
#line 810 "parser.tab.c" // lalr1.cc:859
    break;

  case 52:
#line 212 "parser.y" // lalr1.cc:859
    {}
#line 816 "parser.tab.c" // lalr1.cc:859
    break;

  case 53:
#line 213 "parser.y" // lalr1.cc:859
    {}
#line 822 "parser.tab.c" // lalr1.cc:859
    break;

  case 54:
#line 214 "parser.y" // lalr1.cc:859
    {}
#line 828 "parser.tab.c" // lalr1.cc:859
    break;

  case 55:
#line 215 "parser.y" // lalr1.cc:859
    {}
#line 834 "parser.tab.c" // lalr1.cc:859
    break;

  case 56:
#line 216 "parser.y" // lalr1.cc:859
    {}
#line 840 "parser.tab.c" // lalr1.cc:859
    break;

  case 57:
#line 217 "parser.y" // lalr1.cc:859
    {}
#line 846 "parser.tab.c" // lalr1.cc:859
    break;

  case 58:
#line 218 "parser.y" // lalr1.cc:859
    {}
#line 852 "parser.tab.c" // lalr1.cc:859
    break;

  case 59:
#line 219 "parser.y" // lalr1.cc:859
    {}
#line 858 "parser.tab.c" // lalr1.cc:859
    break;

  case 60:
#line 220 "parser.y" // lalr1.cc:859
    {}
#line 864 "parser.tab.c" // lalr1.cc:859
    break;

  case 61:
#line 221 "parser.y" // lalr1.cc:859
    {}
#line 870 "parser.tab.c" // lalr1.cc:859
    break;

  case 62:
#line 222 "parser.y" // lalr1.cc:859
    {}
#line 876 "parser.tab.c" // lalr1.cc:859
    break;

  case 63:
#line 225 "parser.y" // lalr1.cc:859
    {}
#line 882 "parser.tab.c" // lalr1.cc:859
    break;

  case 64:
#line 228 "parser.y" // lalr1.cc:859
    {}
#line 888 "parser.tab.c" // lalr1.cc:859
    break;

  case 65:
#line 229 "parser.y" // lalr1.cc:859
    {}
#line 894 "parser.tab.c" // lalr1.cc:859
    break;

  case 66:
#line 230 "parser.y" // lalr1.cc:859
    {}
#line 900 "parser.tab.c" // lalr1.cc:859
    break;

  case 67:
#line 231 "parser.y" // lalr1.cc:859
    {}
#line 906 "parser.tab.c" // lalr1.cc:859
    break;

  case 68:
#line 232 "parser.y" // lalr1.cc:859
    {}
#line 912 "parser.tab.c" // lalr1.cc:859
    break;

  case 69:
#line 233 "parser.y" // lalr1.cc:859
    {}
#line 918 "parser.tab.c" // lalr1.cc:859
    break;

  case 70:
#line 234 "parser.y" // lalr1.cc:859
    {}
#line 924 "parser.tab.c" // lalr1.cc:859
    break;

  case 71:
#line 235 "parser.y" // lalr1.cc:859
    {}
#line 930 "parser.tab.c" // lalr1.cc:859
    break;

  case 72:
#line 236 "parser.y" // lalr1.cc:859
    {}
#line 936 "parser.tab.c" // lalr1.cc:859
    break;

  case 73:
#line 237 "parser.y" // lalr1.cc:859
    {}
#line 942 "parser.tab.c" // lalr1.cc:859
    break;

  case 74:
#line 238 "parser.y" // lalr1.cc:859
    {}
#line 948 "parser.tab.c" // lalr1.cc:859
    break;

  case 75:
#line 239 "parser.y" // lalr1.cc:859
    {}
#line 954 "parser.tab.c" // lalr1.cc:859
    break;

  case 76:
#line 240 "parser.y" // lalr1.cc:859
    {}
#line 960 "parser.tab.c" // lalr1.cc:859
    break;

  case 77:
#line 241 "parser.y" // lalr1.cc:859
    {}
#line 966 "parser.tab.c" // lalr1.cc:859
    break;

  case 78:
#line 242 "parser.y" // lalr1.cc:859
    {}
#line 972 "parser.tab.c" // lalr1.cc:859
    break;

  case 79:
#line 243 "parser.y" // lalr1.cc:859
    {}
#line 978 "parser.tab.c" // lalr1.cc:859
    break;

  case 80:
#line 244 "parser.y" // lalr1.cc:859
    {}
#line 984 "parser.tab.c" // lalr1.cc:859
    break;

  case 81:
#line 245 "parser.y" // lalr1.cc:859
    {}
#line 990 "parser.tab.c" // lalr1.cc:859
    break;

  case 82:
#line 246 "parser.y" // lalr1.cc:859
    {}
#line 996 "parser.tab.c" // lalr1.cc:859
    break;

  case 83:
#line 247 "parser.y" // lalr1.cc:859
    {}
#line 1002 "parser.tab.c" // lalr1.cc:859
    break;

  case 84:
#line 248 "parser.y" // lalr1.cc:859
    {}
#line 1008 "parser.tab.c" // lalr1.cc:859
    break;

  case 85:
#line 249 "parser.y" // lalr1.cc:859
    {}
#line 1014 "parser.tab.c" // lalr1.cc:859
    break;

  case 86:
#line 250 "parser.y" // lalr1.cc:859
    {}
#line 1020 "parser.tab.c" // lalr1.cc:859
    break;

  case 87:
#line 251 "parser.y" // lalr1.cc:859
    {}
#line 1026 "parser.tab.c" // lalr1.cc:859
    break;

  case 88:
#line 252 "parser.y" // lalr1.cc:859
    {}
#line 1032 "parser.tab.c" // lalr1.cc:859
    break;

  case 89:
#line 253 "parser.y" // lalr1.cc:859
    {}
#line 1038 "parser.tab.c" // lalr1.cc:859
    break;

  case 90:
#line 254 "parser.y" // lalr1.cc:859
    {}
#line 1044 "parser.tab.c" // lalr1.cc:859
    break;

  case 91:
#line 255 "parser.y" // lalr1.cc:859
    {}
#line 1050 "parser.tab.c" // lalr1.cc:859
    break;


#line 1054 "parser.tab.c" // lalr1.cc:859
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


  const short int parser::yypact_ninf_ = -143;

  const signed char parser::yytable_ninf_ = -25;

  const short int
  parser::yypact_[] =
  {
      11,   -32,    17,  -143,    -2,  -143,    29,    46,     4,  -143,
      78,    -3,    79,    37,  -143,    81,    67,    87,    66,  -143,
      24,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,    45,
      68,  -143,  -143,    70,    94,    54,    83,    82,    90,  -143,
      89,  -143,  -143,  -143,   110,   144,    92,     6,    71,    91,
      97,   106,   107,   239,    24,  -143,  -143,   109,   246,   246,
     -22,  -143,  -143,  -143,  -143,   108,   112,   527,   113,  -143,
     115,    24,  -143,   246,   239,   239,   246,  -143,  -143,   239,
     239,  -143,  -143,   381,   360,   114,   119,   165,  -143,   333,
     -13,  -143,   239,   246,    98,   246,   246,   246,   246,   246,
     121,   187,  -143,    99,   340,   270,   551,   291,   567,   361,
     312,   583,   421,  -143,  -143,   239,   239,   239,   239,   239,
     239,   239,   239,  -143,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   123,  -143,  -143,   401,   596,   501,   125,
     530,   530,   -13,   -13,   -13,  -143,  -143,   208,  -143,  -143,
     227,   227,   227,   227,   111,  -143,   441,   543,   461,    22,
     527,  -143,   527,  -143,   527,  -143,   527,  -143,   481,     1,
     481,     1,   527,   527,   527,   527,   527,   527,   527,   527,
     507,  -143,  -143,  -143,  -143,   243,  -143,   148,   151,  -143,
    -143,  -143,  -143,  -143,    23,   527,   227,   227,  -143,   246,
    -143,  -143,   527
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,     4,     0,     1,     2,     0,     0,     3,
       0,     0,     0,     0,     9,     0,     0,     0,     0,     9,
       0,    21,    19,    20,     6,    24,     8,    11,    10,     0,
      17,    18,    22,     0,     0,     0,     0,     0,     0,     7,
       0,    14,    23,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    26,     0,     0,     0,
      48,    49,    42,    25,    28,    62,     0,    47,    58,    26,
       0,     0,    16,     0,     0,     0,     0,    90,    91,     0,
       0,    48,    62,     0,     0,     0,    22,     0,     5,     0,
      50,    40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    56,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    57,    12,     0,    15,    27,
       0,     0,     0,     0,     0,    88,    64,    80,    65,    81,
      66,    82,    67,    83,    68,    84,    69,    85,    70,    86,
      71,    87,    72,    73,    74,    75,    76,    77,    78,    79,
       0,    60,    36,    37,    63,     0,    13,    29,    30,    33,
      34,    35,    59,    44,     0,    46,     0,     0,    43,     0,
      31,    32,    45
  };

  const short int
  parser::yypgoto_[] =
  {
    -143,  -143,  -143,  -143,  -143,   146,  -143,  -143,    -5,  -143,
     -18,   116,  -143,   118,   -53,  -142,  -143,   -45,  -143,  -143,
     -52,  -143,     7
  };

  const short int
  parser::yydefgoto_[] =
  {
      -1,     2,     6,     3,     9,    17,    26,    27,    62,    47,
      29,    30,    31,    32,    45,    63,    64,    82,   194,    66,
      67,    68,    84
  };

  const short int
  parser::yytable_[] =
  {
      65,    83,    35,    87,   -24,    13,    89,    90,   187,   188,
     189,   190,    28,    93,     1,     4,   101,     5,    94,    14,
       7,   104,   105,   107,   109,   -24,    48,   110,   112,    28,
      21,    70,     8,    22,    23,    71,   126,   127,   128,   129,
     136,   138,    65,   140,   141,   142,   143,   144,   198,   147,
      10,    11,   199,   103,   200,   201,    65,   126,   127,   128,
     129,   130,   131,   156,   158,   160,   162,   164,   166,   168,
     170,    25,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   106,   108,    12,    16,    15,   111,   113,    18,    19,
      33,    20,    36,    21,    37,    38,    22,    23,    20,   137,
      21,    40,    65,    22,    23,    65,    65,    65,    65,    42,
      24,    41,    43,    44,    69,    73,    21,    39,    72,    22,
      23,    74,   157,   159,   161,   163,   165,   167,   169,   171,
      75,    76,    88,   195,    25,    46,    91,   102,   145,   191,
     132,    25,    92,   133,   100,   139,   148,   202,   181,   185,
      21,    65,    65,    22,    23,    49,    50,    25,    51,    52,
      53,   196,    54,    55,   197,    34,    56,    57,    58,     0,
      85,    21,    86,     0,    22,    23,    49,    50,     0,    51,
      52,    53,     0,    54,    55,     0,    59,    56,   134,    58,
       0,    60,    61,    21,     0,     0,    22,    23,    49,    50,
       0,    51,    52,    53,     0,    54,    55,    59,     0,    56,
     146,    58,    60,    61,    21,     0,     0,    22,    23,    49,
      50,     0,    51,    52,    53,     0,    54,    55,     0,    59,
      56,   186,    58,    21,    60,    61,    22,    23,    49,    50,
       0,    51,    52,    53,     0,    54,    55,     0,     0,    56,
      59,    58,     0,     0,     0,    60,    61,    54,    55,    77,
      78,    54,    55,    79,    54,    55,     0,    58,   193,    59,
      58,    80,     0,     0,    60,    61,     0,     0,     0,     0,
       0,    59,     0,     0,     0,    59,    81,    61,    59,     0,
      81,    61,     0,    81,    61,   150,    93,     0,     0,     0,
       0,    94,     0,   115,   116,   117,   118,   119,   120,   121,
     122,    95,    96,    97,    98,    99,   152,    93,     0,     0,
       0,     0,    94,     0,   115,   116,   117,   118,   119,   120,
     121,   122,    95,    96,    97,    98,    99,   135,    93,     0,
       0,     0,     0,    94,     0,   115,   116,   117,   118,   119,
     120,   121,   122,    95,    96,    97,    98,    99,   135,    93,
       0,     0,     0,     0,    94,   149,    93,     0,     0,     0,
       0,    94,     0,     0,    95,    96,    97,    98,    99,     0,
       0,    95,    96,    97,    98,    99,   154,    93,   123,     0,
       0,     0,    94,   124,   125,   126,   127,   128,   129,   130,
     131,     0,    95,    96,    97,    98,    99,    93,     0,   114,
       0,     0,    94,     0,   115,   116,   117,   118,   119,   120,
     121,   122,    95,    96,    97,    98,    99,    93,     0,   182,
       0,     0,    94,     0,   115,   116,   117,   118,   119,   120,
     121,   122,    95,    96,    97,    98,    99,    93,     0,     0,
       0,     0,    94,     0,   115,   116,   117,   118,   119,   120,
     121,   122,    95,    96,    97,    98,    99,    93,     0,     0,
       0,     0,    94,     0,     0,   116,   117,   118,   119,   120,
     121,   122,    95,    96,    97,    98,    99,    93,     0,     0,
       0,     0,    94,     0,     0,     0,   117,   118,   119,   120,
     121,   122,    95,    96,    97,    98,    99,    93,     0,     0,
       0,     0,    94,     0,     0,     0,   117,   118,   119,   120,
       0,     0,    95,    96,    97,    98,    99,    93,   184,     0,
       0,     0,    94,    93,   192,     0,     0,     0,    94,     0,
       0,     0,    95,    96,    97,    98,    99,     0,    95,    96,
      97,    98,    99,    93,     0,     0,    93,     0,    94,     0,
       0,    94,     0,     0,     0,     0,     0,     0,    95,    96,
      97,    98,    99,    97,    98,    99,   151,   125,   126,   127,
     128,   129,   130,   131,   124,   125,   126,   127,   128,   129,
     130,   131,   153,     0,     0,     0,     0,     0,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   155,     0,
       0,     0,     0,     0,     0,     0,   124,   125,   126,   127,
     128,   129,   130,   131,   183,     0,     0,     0,     0,   124,
     125,   126,   127,   128,   129,   130,   131
  };

  const short int
  parser::yycheck_[] =
  {
      45,    53,    20,    56,    26,     8,    58,    59,   150,   151,
     152,   153,    17,    26,     3,    47,    69,     0,    31,    22,
      22,    73,    74,    75,    76,    47,    44,    79,    80,    34,
       6,    25,     3,     9,    10,    29,    35,    36,    37,    38,
      92,    93,    87,    95,    96,    97,    98,    99,    25,   102,
       4,    47,    29,    71,   196,   197,   101,    35,    36,    37,
      38,    39,    40,   115,   116,   117,   118,   119,   120,   121,
     122,    47,   124,   125,   126,   127,   128,   129,   130,   131,
     132,    74,    75,     5,    47,     6,    79,    80,     7,    22,
      24,     4,    47,     6,    26,    25,     9,    10,     4,    92,
       6,    47,   147,     9,    10,   150,   151,   152,   153,    27,
      23,    28,    22,    24,    22,    24,     6,    23,    47,     9,
      10,    24,   115,   116,   117,   118,   119,   120,   121,   122,
      24,    24,    23,   185,    47,    25,    28,    22,    17,    28,
      26,    47,    30,    24,    31,    47,    47,   199,    25,    24,
       6,   196,   197,     9,    10,    11,    12,    47,    14,    15,
      16,    13,    18,    19,    13,    19,    22,    23,    24,    -1,
      54,     6,    54,    -1,     9,    10,    11,    12,    -1,    14,
      15,    16,    -1,    18,    19,    -1,    42,    22,    23,    24,
      -1,    47,    48,     6,    -1,    -1,     9,    10,    11,    12,
      -1,    14,    15,    16,    -1,    18,    19,    42,    -1,    22,
      23,    24,    47,    48,     6,    -1,    -1,     9,    10,    11,
      12,    -1,    14,    15,    16,    -1,    18,    19,    -1,    42,
      22,    23,    24,     6,    47,    48,     9,    10,    11,    12,
      -1,    14,    15,    16,    -1,    18,    19,    -1,    -1,    22,
      42,    24,    -1,    -1,    -1,    47,    48,    18,    19,    20,
      21,    18,    19,    24,    18,    19,    -1,    24,    25,    42,
      24,    32,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    42,    -1,    -1,    -1,    42,    47,    48,    42,    -1,
      47,    48,    -1,    47,    48,    25,    26,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    25,    26,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    25,    26,    -1,
      -1,    -1,    -1,    31,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    25,    26,
      -1,    -1,    -1,    -1,    31,    25,    26,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    41,    42,    43,    44,    45,    -1,
      -1,    41,    42,    43,    44,    45,    25,    26,    28,    -1,
      -1,    -1,    31,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    41,    42,    43,    44,    45,    26,    -1,    28,
      -1,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    26,    -1,    28,
      -1,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    26,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    26,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    26,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    26,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    35,    36,    37,    38,
      -1,    -1,    41,    42,    43,    44,    45,    26,    27,    -1,
      -1,    -1,    31,    26,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    -1,    41,    42,
      43,    44,    45,    26,    -1,    -1,    26,    -1,    31,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    43,    44,    45,    25,    34,    35,    36,
      37,    38,    39,    40,    33,    34,    35,    36,    37,    38,
      39,    40,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    28,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    40
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
      47,    48,    57,    64,    65,    66,    68,    69,    70,    22,
      25,    29,    47,    24,    24,    24,    24,    20,    21,    24,
      32,    47,    66,    69,    71,    60,    62,    63,    23,    69,
      69,    28,    30,    26,    31,    41,    42,    43,    44,    45,
      31,    63,    22,    59,    69,    69,    71,    69,    71,    69,
      69,    71,    69,    71,    28,    33,    34,    35,    36,    37,
      38,    39,    40,    28,    33,    34,    35,    36,    37,    38,
      39,    40,    26,    24,    23,    25,    69,    71,    69,    47,
      69,    69,    69,    69,    69,    17,    23,    63,    47,    25,
      25,    25,    25,    25,    25,    25,    69,    71,    69,    71,
      69,    71,    69,    71,    69,    71,    69,    71,    69,    71,
      69,    71,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    25,    28,    28,    27,    24,    23,    64,    64,    64,
      64,    28,    27,    25,    67,    69,    13,    13,    25,    29,
      64,    64,    69
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    49,    50,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    61,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    65,    66,    66,    67,    67,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,    13,     5,     7,     2,     0,
       1,     1,     8,     9,     3,     4,     2,     1,     1,     1,
       1,     1,     1,     3,     1,     2,     0,     4,     1,     5,
       5,     7,     7,     5,     5,     5,     4,     4,     3,     3,
       2,     3,     1,     6,     5,     3,     1,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     1,     5,
       4,     1,     1,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     1
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
  "lvalue", "expression", "array_access", "logical_expression", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,   125,   125,   128,   129,   132,   135,   136,   139,   140,
     143,   144,   147,   148,   151,   154,   155,   158,   159,   162,
     163,   164,   165,   168,   170,   173,   174,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   194,   197,   198,   201,   202,   205,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   225,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255
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
#line 1557 "parser.tab.c" // lalr1.cc:1167
#line 256 "parser.y" // lalr1.cc:1168

