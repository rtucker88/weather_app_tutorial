let app = Express.express();
let port = 5000;

/*Setup our router*/
let router = Express.router(~caseSensitive=true, ~strict=true, ());

Express.Router.use(router, Express.Middleware.json(~limit=5.0 |> Express.ByteLimit.mb, ()));
Express.Router.use(router, Express.Middleware.urlencoded(~extended=true, ()));
Express.App.useRouterOnPath(app, ~path="/", router);

SearchLocations.Routes.routes(router);

Express.Router.get(router, ~path="/") @@ Express.Middleware.from((_, _) => Express.Response.sendString("PORT 5000"));

Express.App.get(app, ~path="/error") @@
Express.Middleware.from((_, _, res) =>
  res
  |> Express.Response.status(Express.Response.StatusCode.InternalServerError)
  |> Express.Response.sendString("Internal Server Error")
);

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://localhost:5000"
  };

let server = Express.App.listen(app, ~port, ~onListen, ());
