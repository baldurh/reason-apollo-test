let ste = ReasonReact.string;

module Collection = {
  type t('a) = {
    total: int,
    items: list('a),
  };

  let parse = (parser, json) =>
    Json.Decode.{
      total: json |> field("total", int),
      items: json |> field("items", list(parser)),
    };
};

module TravelAlert = {
  type t = {
    title: option(string),
    url: option(string),
    expiryDate: option(Js.Date.t),
  };
};

module Site = {
  type t = {
    region: string,
    text: option(string),
    travelAlert: option(TravelAlert.t),
  };

  let parse = json =>
    Json.Decode.{
      region: json |> field("region", withDefault("us", string)),
      text: json |> optional(field("text", string)),
      travelAlert: None,
    };
};

module QueryRoot = {
  type t = {
    site: option(Site.t),
    siteCollection: option(Collection.t(Site.t)),
  };

  let parse = json =>
    Json.Decode.{
      site: json |> optional(field("site", Site.parse)),
      siteCollection:
        json
        |> optional(field("siteCollection", Collection.parse(Site.parse))),
    };
};

module QueryConfig: ReasonApolloTypes.Config = {
  include QueryRoot;
  let query = "query getSiteSettings($region: String!, $locale: String!) {
    siteCollection(where: {region: $region}, locale: $locale) {
      total
      items {
        region
        text
        travelAlert {
          title
          url
          expiryDate
        }
      }
    }
  }";
};

module SiteSettingsQuery = ReasonApollo.CreateQuery(QueryConfig);

let component = ReasonReact.statelessComponent("FrontPage");

type variables = {
  region: string,
  locale: string,
};

let encodeVariables = variables =>
  Json.Encode.(
    object_([
      ("region", string(variables.region)),
      ("locale", string(variables.locale)),
    ])
  );

let make = _children => {
  ...component,
  render: _self => {
    <SiteSettingsQuery
      variables={encodeVariables({region: "is", locale: "is-IS"})}>
        ...{({result}) => {
          switch (result) {
          | Data(result) => {
            let foo : QueryRoot.t = result; /* This forces a more explicit compiler error */
            Js.log(result.siteCollection) /* The record field siteCollection can't be found. */
          }
          | _ => ()
          };
          ste("foo");
        }}
      </SiteSettingsQuery>;
  },
};