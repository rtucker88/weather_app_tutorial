let apiId = "<INSERT_API_HERE>";

module Body = {
  type payload = {zipcode: string};

  let jsonDecoder = json => Json.Decode.{zipcode: Json.Decode.field("zipcode", Json.Decode.string, json)};
  let encoder = body => Json.Encode.object_([("zipcode", body.zipcode |> Json.Encode.string)]);
};

let raiseIfNone =
  fun
  | Some(value) => value
  | None => failwith("Body is none");

module Routes = {
  let routes = router => {
    Express.Router.post(router, ~path="/search-location") @@
    Express.Middleware.from((res, req) =>
      Express.Request.bodyJSON(req)
      |> raiseIfNone
      |> Body.jsonDecoder
      |> (json => Js.String.length(json.zipcode))
      |> (
        zipcode =>
          switch (zipcode) {
          | zipcode when zipcode === 5 => Express.Response.redirect("/current-weather")
          | _ => Express.Response.redirect("/error")
          }
      )
    );

    Express.Router.get(router, ~path="/search-location-weather/:zipcode") @@
    Express.PromiseMiddleware.from((next, req, res) =>
      Js.Promise.make((~resolve, ~reject) =>
        Js.Dict.get(Express.Request.params(req), "zipcode")
        |> (
          zipcode =>
            switch (zipcode) {
            | None => next(Express.Next.route, res) |> failwith("Zipcode isn't defined")
            | Some(value) => Js.Json.stringify(value) |> Js.String.replace("\"", "") |> Js.String.replace("\"", "")
            }
        )
        |> (
          zipcode => {
            let length = Js.String.length(zipcode);
            switch (zipcode) {
            | zipcode when length === 5 =>
              /*Here we use the API with the user's zipcode*/
              let baseUrl = "http://api.openweathermap.org/data/2.5/weather?zip=";
              let apiId = {j|,us&appid=$(apiId)&units=imperial|j};
              let fullUrl = {j|$(baseUrl)$(zipcode)$(apiId)|j};

              let _ =
                Js.Promise.(
                  Bs_node_fetch.fetch(fullUrl)
                  |> then_(Bs_node_fetch.Response.json)
                  |> then_(str => Express.Response.sendJson(str, res) |> resolve)
                  |> catch(_ => next(Express.Next.route, res) |> resolve)
                );
              ();
            | _ => resolve(. next(Express.Next.route, res))
            };
          }
        )
      )
    );
  };
};
