// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var ApolloProvider = require("reason-apollo/src/ApolloProvider.bs.js");
var Page$ReactTemplate = require("./Page.bs.js");
var Client$ReactTemplate = require("./Client.bs.js");

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, ApolloProvider.make(Client$ReactTemplate.instance, /* array */[ReasonReact.element(undefined, undefined, Page$ReactTemplate.make(/* array */[]))])), "index");

/*  Not a pure module */