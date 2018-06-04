let component = ReasonReact.statelessComponent("ErrorDisplay");
let make = (_children) => {
  ...component,
  render: _self =>
       <div>
        <div className='header'>
          <h2>(ReactReason.ReactString("Error"))</h2>
        </div>
      </div>,
};
