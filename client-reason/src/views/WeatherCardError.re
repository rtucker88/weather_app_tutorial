let component = ReasonReact.statelessComponent("WeatherCardError");

/* Handle the "try again" action */
let handleClick = (_event, _self) => ReasonReact.Router.push("/");

let make = (_children) => {
  ...component,
  render: self => <div className='weatherCardContainer'>
                          <div className='weatherCardError'>
                            <img src={NoLocationFound} alt='no location found'/>
                            <p>(ReasonReact.string("Whoa! Looks like there was an error with your zipcode.")</p>
                            <button onClick=(_event => self.handle(handleClick))>(ReasonReact.string("Try Again"))</button>
                          </div>
                        </div>,
};
