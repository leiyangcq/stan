#ifndef STAN_LANG_GRAMMARS_VAR_DECLS_GRAMMAR_DEF_HPP
#define STAN_LANG_GRAMMARS_VAR_DECLS_GRAMMAR_DEF_HPP

#include <stan/lang/ast.hpp>
#include <stan/lang/grammars/var_decls_grammar.hpp>
#include <stan/lang/grammars/common_adaptors_def.hpp>
#include <stan/lang/grammars/semantic_actions.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <set>
#include <string>
#include <vector>

BOOST_FUSION_ADAPT_STRUCT(stan::lang::int_var_decl,
                          (stan::lang::range, range_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::double_var_decl,
                          (stan::lang::range, range_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::vector_var_decl,
                          (stan::lang::range, range_)
                          (stan::lang::expression, M_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::row_vector_var_decl,
                          (stan::lang::range, range_)
                          (stan::lang::expression, N_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::matrix_var_decl,
                          (stan::lang::range, range_)
                          (stan::lang::expression, M_)
                          (stan::lang::expression, N_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::unit_vector_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::simplex_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::ordered_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::positive_ordered_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::cholesky_factor_var_decl,
                          (stan::lang::expression, M_)
                          (stan::lang::expression, N_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::cholesky_corr_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::cov_matrix_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

BOOST_FUSION_ADAPT_STRUCT(stan::lang::corr_matrix_var_decl,
                          (stan::lang::expression, K_)
                          (std::string, name_)
                          (std::vector<stan::lang::expression>, dims_) )

namespace stan {

  namespace lang {

    template <typename Iterator>
    var_decls_grammar<Iterator>::var_decls_grammar(variable_map& var_map,
                                               std::stringstream& error_msgs)
      : var_decls_grammar::base_type(var_decls_r),
        var_map_(var_map),
        error_msgs_(error_msgs),
        expression_g(var_map, error_msgs),
        expression07_g(var_map, error_msgs, expression_g) {
      using boost::spirit::qi::_1;
      using boost::spirit::qi::_3;
      using boost::spirit::qi::char_;
      using boost::spirit::qi::eps;
      using boost::spirit::qi::lexeme;
      using boost::spirit::qi::lit;
      using boost::spirit::qi::no_skip;
      using boost::spirit::qi::_pass;
      using boost::spirit::qi::_val;
      using boost::spirit::qi::labels::_a;
      using boost::spirit::qi::labels::_r1;
      using boost::spirit::qi::labels::_r2;

      var_decls_r.name("variable declarations");
      var_decls_r
        %= *(var_decl_r(_r1, _r2));

      // _a = error state local,
      // _r1 constraints allowed inherited,
      // _r2 var_origin
      var_decl_r.name("variable declaration");
      var_decl_r
        %= (int_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs))]
            | double_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | vector_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | row_vector_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | matrix_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | unit_vector_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | simplex_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | ordered_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | positive_ordered_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | cholesky_factor_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                              boost::phoenix::ref(error_msgs_))]
            | cholesky_corr_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                              boost::phoenix::ref(error_msgs_))]
            | cov_matrix_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            | corr_matrix_decl_r(_r2)
            [add_var_f(_val, _1, boost::phoenix::ref(var_map_), _a, _r2,
                       boost::phoenix::ref(error_msgs_))]
            )
        > eps
          [validate_decl_constraints_f(_r1, _a, _val, _pass,
                                       boost::phoenix::ref(error_msgs_))]

        > lit(';');

      int_decl_r.name("integer declaration");
      int_decl_r
        %= (lit("int")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > -range_brackets_int_r(_r1)
        > identifier_r
        > opt_dims_r(_r1);

      double_decl_r.name("real declaration");
      double_decl_r
        %= (lit("real")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > -range_brackets_double_r(_r1)
        > identifier_r
        > opt_dims_r(_r1);

      vector_decl_r.name("vector declaration");
      vector_decl_r
        %= (lit("vector")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > -range_brackets_double_r(_r1)
        > lit('[')
        > expression_g(_r1)
        [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      row_vector_decl_r.name("row vector declaration");
      row_vector_decl_r
        %= (lit("row_vector")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > -range_brackets_double_r(_r1)
        > lit('[')
        > expression_g(_r1)
        [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      matrix_decl_r.name("matrix declaration");
      matrix_decl_r
        %= (lit("matrix")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > -range_brackets_double_r(_r1)
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(',')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      unit_vector_decl_r.name("unit_vector declaration");
      unit_vector_decl_r
        %= (lit("unit_vector")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      simplex_decl_r.name("simplex declaration");
      simplex_decl_r
        %= (lit("simplex")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      ordered_decl_r.name("ordered declaration");
      ordered_decl_r
        %= (lit("ordered")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      positive_ordered_decl_r.name("positive_ordered declaration");
      positive_ordered_decl_r
        %= (lit("positive_ordered")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      cholesky_factor_decl_r.name("cholesky factor for symmetric,"
                                  " positive-def declaration");
      cholesky_factor_decl_r
        %= (lit("cholesky_factor_cov")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > -(lit(',')
            > expression_g(_r1)
            [validate_int_expr_f(_1, _pass,
                                   boost::phoenix::ref(error_msgs_))])
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1)
        > eps
        [copy_square_cholesky_dimension_if_necessary_f(_val)];

      cholesky_corr_decl_r.name("cholesky factor for"
                                " correlation matrix declaration");
      cholesky_corr_decl_r
        %= (lit("cholesky_factor_corr")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      cov_matrix_decl_r.name("covariance matrix declaration");
      cov_matrix_decl_r
        %= (lit("cov_matrix")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      corr_matrix_decl_r.name("correlation matrix declaration");
      corr_matrix_decl_r
        %= (lit("corr_matrix")
            >> no_skip[!char_("a-zA-Z0-9_")])
        > lit('[')
        > expression_g(_r1)
          [validate_int_expr_f(_1, _pass, boost::phoenix::ref(error_msgs_))]
        > lit(']')
        > identifier_r
        > opt_dims_r(_r1);

      opt_dims_r.name("array dimensions (optional)");
      opt_dims_r
        %=  - dims_r(_r1);

      dims_r.name("array dimensions");
      dims_r
        %= lit('[')
        > (expression_g(_r1)
           [validate_int_data_expr_f(_1, _r1, _pass,
                                     boost::phoenix::ref(var_map_),
                                     boost::phoenix::ref(error_msgs_))]
           % ',')
        > lit(']');

      range_brackets_int_r.name("integer range expression pair, brackets");
      range_brackets_int_r
        = lit('<') [empty_range_f(_val, boost::phoenix::ref(error_msgs_))]
        >> (
            ((lit("lower")
              >> lit('=')
              >> expression07_g(_r1)
                 [set_int_range_lower_f(_val, _1, _pass,
                                        boost::phoenix::ref(error_msgs_))])
             >> -(lit(',')
                  >> lit("upper")
                  >> lit('=')
                  >> expression07_g(_r1)
                     [set_int_range_upper_f(_val, _1, _pass,
                                            boost::phoenix::ref(error_msgs_))]))
           |
           (lit("upper")
            >> lit('=')
            >> expression07_g(_r1)
               [set_int_range_upper_f(_val, _1, _pass,
                                      boost::phoenix::ref(error_msgs_))])
            )
        >> lit('>');

      range_brackets_double_r.name("real range expression pair, brackets");
      range_brackets_double_r
        = lit('<')[empty_range_f(_val, boost::phoenix::ref(error_msgs_))]
        > (
           ((lit("lower")
             > lit('=')
             > expression07_g(_r1)
               [set_double_range_lower_f(_val, _1, _pass,
                                         boost::phoenix::ref(error_msgs_))])
             > -(lit(',')
                 > lit("upper")
                 > lit('=')
                 > expression07_g(_r1)
                   [set_double_range_upper_f(_val, _1, _pass,
                                         boost::phoenix::ref(error_msgs_))]))
           |
           (lit("upper")
            > lit('=')
            > expression07_g(_r1)
              [set_double_range_upper_f(_val, _1, _pass,
                                        boost::phoenix::ref(error_msgs_))])
            )
        > lit('>');

      identifier_r.name("identifier");
      identifier_r
        %= identifier_name_r
           [validate_identifier_f(_val, _pass,
                                  boost::phoenix::ref(error_msgs_))];

      identifier_name_r.name("identifier subrule");
      identifier_name_r
        %= lexeme[char_("a-zA-Z")
                  >> *char_("a-zA-Z0-9_.")];
    }
  }


}
#endif

