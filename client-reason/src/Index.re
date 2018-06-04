let component = ReasonReact.reducerComponent("WeatherApp");

let make = _children => {
    ...component,
    reducer: (action, state) =>
    switch (action) {

    },
    didMount: self => {
        let watcherId = ReactReason.Router.watchUrl(url => {
            switch (url.hash) {

            }
        });
        self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
    }
};
