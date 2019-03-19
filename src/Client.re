/* open ApolloLinks; */
open ApolloInMemoryCache;

/* Create an InMemoryCache */
let inMemoryCache =
  createInMemoryCache(());

/* Create an HTTP Link */
let httpLink = ApolloLinks.createHttpLink(~uri="https://graphql.contentful.com/content/v1/spaces/dxe8mxf52fib/?access_token=xxx", ());


let instance = ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());
